#include "converter.h"

const char* MENCODER_PATH = "/usr/bin/mencoder";
const int DEFAULT_FPS = 25;
const int TARGET_FPS = 10;

Converter::Converter(QString source, QString target, QObject *parent) :
    QThread(parent), srcFileName(source), trgFileName(target),
    startPos(-1), endPos(-1)
{
}

void Converter::setClipBounds(int start, int end)
{
    float k = DEFAULT_FPS / TARGET_FPS;
    startPos = float(start) / 1000 / k;
    endPos = float(end - start) / 1000 / k;
}

// Monitor encoding progress and emit on change
void Converter::watchForProgress(QProcess &mencProc)
{
    qDebug("MENCODER conversion progress:");
    while(mencProc.state() != QProcess::NotRunning) {
        mencProc.waitForReadyRead();
        QString line = mencProc.readLine();
        if(line.startsWith("Pos:")) {
            emit progressChanged();
            qDebug(line.toAscii().data());
        }
    }
}

void Converter::run()
{
    QStringList cmdLine;
    cmdLine << "mencoder";
    cmdLine << QString("\"%1\"").arg(this->srcFileName)
            << "-ovc lavc" << QString("-fps %1").arg(TARGET_FPS);

    // Clip boundaries
    if(startPos > -0.1 && endPos > -0.1) {
        cmdLine << QString("-ss %1 -endpos %2")
                   .arg(QString::number(startPos, 'f', 2),
                        QString::number(endPos, 'f', 2));
    }

    cmdLine << QString("-o \"%1\"").arg(this->trgFileName);

    QProcess convProc;
    convProc.setProcessChannelMode(QProcess::MergedChannels);
    QString cmd = cmdLine.join(" ");
    convProc.start(cmd);

    watchForProgress(convProc);

    emit finished();
}

// Check if mencoder installed
bool Converter::canConvert()
{
    return QFile::exists(MENCODER_PATH);
}
