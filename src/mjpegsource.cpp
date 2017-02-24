#include "mjpegsource.h"

const int MIN_LENGTH = 1024;
const int RECONNECT_INTERVAL = 10000;
const int CHECK_MANUAL_RECONNECT_INTERVAL = 15000;
const int HANG_INTERVAL = 20000;

MJPegSource::MJPegSource(QString mjpegUrl, QObject *parent) :
    QObject(parent), manager(this), isReconnectPlanned(false), mjpegUrl(mjpegUrl)
{
    this->status = Normal;
    connect(&hangDetector, SIGNAL(timeout()), SLOT(sourceHung()));
}

// Start the video source
void MJPegSource::start()
{
    isReconnectPlanned = false;
    status = Connecting;

    // Video request
    QUrl mjpegRequestUrl(mjpegUrl);
    QNetworkRequest mjpegReq(mjpegRequestUrl);

    // Authentication
    QString authHash = Config::getInstance()->getAuthHash();
    if(authHash.length() > 0) {
        QString authValue = QString("Basic ").append(authHash);
        mjpegReq.setRawHeader("Authorization", QByteArray(authValue.toAscii().data()));
    }

    mjpegResponse = manager.get(mjpegReq);
    connect(mjpegResponse, SIGNAL(error(QNetworkReply::NetworkError)),
                           SLOT(onError(QNetworkReply::NetworkError)));
    connect(mjpegResponse, SIGNAL(finished()), SLOT(requestFinished()));
    connect(mjpegResponse, SIGNAL(readyRead()), SLOT(mjpegDataRead()));

    this->nextFrameLength = 0;
    this->nthFrameToSkip = -1;
    this->frameNumber = 0;
    hangDetector.start(HANG_INTERVAL);
}

// Try reconnect source if error occured
void MJPegSource::reconnect()
{
    QTimer delay;

    int interval = this->status != Rejected ?
                RECONNECT_INTERVAL :
                CHECK_MANUAL_RECONNECT_INTERVAL;
    delay.singleShot(interval, this, SLOT(start()));

    isReconnectPlanned = true;

    QNetworkSession session(manager.configuration());
    if(mjpegResponse != NULL && session.isOpen()) {
        session.stop();
        mjpegResponse->deleteLater();
    }

    emit error();
}

void MJPegSource::toggleFrameSkip(bool enabled)
{
    this->nthFrameToSkip = enabled ? 2 : -1;
}

void MJPegSource::updateUrl(QString newMjpegUrl)
{
    this->mjpegUrl = newMjpegUrl;
    this->status = BrokenConnection;
    this->reconnect();
}

void MJPegSource::mjpegDataRead()
{
    status = Normal;

    if(nextFrameLength == 0) {
        // Read frame length
        nextFrameLength = MJpegHelpers::getFrameLength(mjpegResponse);
    } else if(mjpegResponse->bytesAvailable() >= nextFrameLength) {
        // Read frame data
        hangDetector.stop();
        QByteArray frameData = mjpegResponse->read(nextFrameLength);
        if(nthFrameToSkip < 0 || frameNumber % nthFrameToSkip > 0) {
            if(frameData.length() >= MIN_LENGTH) {
                emit frameReceived(frameData);
            }
        }
        hangDetector.start(HANG_INTERVAL);

        // Discard the rest data in buffer
        mjpegResponse->readAll();

        nextFrameLength = 0;
        frameNumber++;
    }
}

// Get human readable source status
QString MJPegSource::getStatusDescription()
{
    QString descr;
    if(status == Connecting) {
        descr = "connecting";
    } else if(status == Hang) {
        descr = "data stream error";
    } else if(status == Rejected) {
        descr = "connection rejected";
    } else if(status != Normal) {
        descr = "connection failure";
    }
    return descr;
}

// REGION: Error handling
void MJPegSource::requestFinished()
{
    qDebug() << QString("%1 - unexpected end!").arg(this->mjpegUrl);
    if(status != Hang && !isReconnectPlanned) {
        status = BrokenConnection;
        reconnect();
    }
}

void MJPegSource::onError(QNetworkReply::NetworkError error)
{
    bool isRefused = error == QNetworkReply::ConnectionRefusedError ||
            error == QNetworkReply::RemoteHostClosedError;
    qDebug() << QString("%1 - network error (%2d)!").arg(this->mjpegUrl).arg(int(error));
    if(status != Hang && status != FailedToConnect && !isReconnectPlanned) {
        if(isRefused) {
            status = Rejected;
        } else {
            status = FailedToConnect;
        }
        reconnect();
    }
}

void MJPegSource::sourceHung()
{
    qDebug() << QString("%1 - hang detected!").arg(this->mjpegUrl);
    if(status == Normal) {
        status = Hang;
        hangDetector.stop();
        mjpegResponse->close();
        reconnect();
    } else if(status == Connecting) {
        this->onError(QNetworkReply::TimeoutError);
    }
}
// ENDREGION
