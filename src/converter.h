#ifndef CONVERTER_H
#define CONVERTER_H

#include <QThread>
#include <QProcess>
#include <QFile>

// Converter thread that uses an external converter
// for converting MJPEG to MP4
class Converter : public QThread
{
    Q_OBJECT
public:
    explicit Converter(QString source, QString target, QObject *parent = 0);
    static bool canConvert();
    void setClipBounds(int start, int end);
    void run();

signals:
    void progressChanged();
    void finished();

private:
    QString srcFileName, trgFileName;
    float startPos, endPos;
    void watchForProgress(QProcess &mencProc);
    
};

#endif // CONVERTER_H
