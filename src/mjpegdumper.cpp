#include "mjpegdumper.h"

MJpegDumper::MJpegDumper(QString name, QObject *parent) :
    QThread(parent), sourceName(name), dumpFile(NULL)
{
    this->jpegQuality = -1;
    QObject::moveToThread(this);
}

void MJpegDumper::run()
{
    this->setPriority(QThread::LowPriority);
    exec();
}

// Write new frame to record file
void MJpegDumper::dumpFrameData(QByteArray *frameData)
{
    QByteArray *savingData = NULL;
    int jpegQuality = Config::getInstance()->getJpegQuality();
    bool needRecode = jpegQuality != -1;

    QByteArray imageData;
    QBuffer imageBuffer(&imageData);
    if(needRecode) {
        // Recode JPEG with given quality (if needed)
        QImage imgFrame = QImage::fromData(*frameData);
        imageBuffer.open(QIODevice::WriteOnly);
        imgFrame.save(&imageBuffer, "JPG", jpegQuality);
        savingData = &imageData;
    } else {
        savingData = frameData;
    }

    // Write headers and timestamp
    dumpFile->write("--dump_frame_boundary\n");
    long mSecsSinceStart = startedAt.msecsTo(QDateTime::currentDateTime());
    QByteArray msPassed(QString("X-Timestamp: %1\n").arg(mSecsSinceStart).toAscii().data());
    dumpFile->write(msPassed);
    dumpFile->write("Content-Type: image/jpeg\n");
    QByteArray cl(QString("Content-Length: %1\n").arg(savingData->length()).toAscii().data());

    // Write frame data
    dumpFile->write(cl);
    dumpFile->write("\n");
    dumpFile->write(*savingData);

    if(needRecode) {
        imageBuffer.close();
    }
}

// Change output directory's name
void MJpegDumper::updateSourceName(QString newName)
{
    this->sourceName = newName;
}

QString MJpegDumper::getDumpDirectory()
{
    QDateTime now = QDateTime::currentDateTime();
    QString baseDir = Config::getInstance()->getDumpDir();
    QDir userHome(baseDir);
    QString dateDir = QString("%1/%2/%3").arg(baseDir, sourceName, now.toString("dd_MM_yyyy"));
    userHome.mkpath(dateDir);

    QString path = QString("%1/%2.mjpeg").arg(dateDir, now.toString("hh_mm_ss"));
    return path;
}

// Start dumping new record
void MJpegDumper::beginDump()
{
    dumpFile = new QFile(getDumpDirectory());
    dumpFile->open(QIODevice::WriteOnly);
    this->startedAt = QDateTime::currentDateTime();
}

// End dump
void MJpegDumper::endDump()
{
    if(dumpFile != NULL) {
        dumpFile->close();
    }
}
