#ifndef MJPEGSOURCE_H
#define MJPEGSOURCE_H

#include <QObject>
#include <QUrl>
#include <QtNetwork/QtNetwork>
#include "config.h"
#include "mjpeghelpers.h"
#include "data.h"

// Gathers frames from MJPEG source
class MJPegSource : public QObject
{
    Q_OBJECT
public:
    // Status of camera video source
    enum SourceStatus {
        Connecting,
        Normal,
        BrokenConnection,
        FailedToConnect,
        Hang,
        Rejected,
        InvalidCredentials
    };

    explicit MJPegSource(QString, QObject *parent = 0);
    void toggleFrameSkip(bool enabled);
    void updateUrl(QString newMjpegUrl);
    bool ok() { return this->status == Normal; }
    QString getStatusDescription();

    inline MJPegSource::SourceStatus getStatus() { return this->status; }
    inline QString &getUrl() { return this->mjpegUrl; }

public slots:
    void start();

signals:
    void frameReceived(QByteArray &data);
    void error();

private:
    void reconnect();

    QNetworkAccessManager manager;
    QNetworkReply *mjpegResponse;
    QByteArray buffer;

    QTimer hangDetector;
    bool isReconnectPlanned;

    QString mjpegUrl;

    SourceStatus status;
    int nextFrameLength;
    int nthFrameToSkip;
    uint frameNumber;

private slots:
    void requestFinished();
    void onError(QNetworkReply::NetworkError error);
    void sourceHung();
    void mjpegDataRead();
};

#endif // MJPEGSOURCE_H
