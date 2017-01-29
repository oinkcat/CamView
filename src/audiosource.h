#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <QThread>
#include <QtNetwork/QtNetwork>
#include <QAudioOutput>
#include "alawdecoder.h"

class AudioSource : public QThread
{
    Q_OBJECT
public:
    explicit AudioSource(QString url);
    ~AudioSource();
    void run();
    inline bool isRunning() { return playing; }
    
private:
    void applyVolumeOffset(QByteArray *data);
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QAudioOutput *audioOut;
    QIODevice *audio;
    QBuffer *audioBuffer;
    QUrl audioUrl;
    bool playing;
    int volumeOffset;

signals:

public slots:
    void setVolumeOffset(int offset) { this->volumeOffset = offset; }

private slots:
    void dataReady();
    
};

#endif // AUDIOSOURCE_H
