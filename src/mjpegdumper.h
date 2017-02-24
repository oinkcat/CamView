#ifndef MJPEGDUMPER_H
#define MJPEGDUMPER_H

#include <QObject>
#include <QThread>
#include <QPixmap>
#include <QBuffer>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include "config.h"

// MJPEG stream recorder
class MJpegDumper : public QThread
{
    Q_OBJECT
public:
    explicit MJpegDumper(QString name, QObject *parent = 0);
    void run();
    void updateSourceName(QString newName);
    
signals:
    
public slots:
    void beginDump();
    void endDump();
    void dumpFrameData(QByteArray &frameData);
    
private:
    QString getDumpDirectory();
    QFile *dumpFile;
    QString sourceName;
    QDateTime startedAt;
    int jpegQuality;
};

#endif // MJPEGDUMPER_H
