#include "audiosource.h"

const int K_R = 10;
const int MAX_OFFSET = 10;
const int MAX_BYTE = 255;
const int MAX_BASE = 200;

// Audio source in separate thread
AudioSource::AudioSource(QString url) :
    QThread(), playing(false), volumeOffset(0)
{
    this->audioUrl = QUrl(url);
    QObject::moveToThread(this);
}

// Adjust volume of audio stream
void AudioSource::applyVolumeOffset(QByteArray *data)
{
    float k = (float)(volumeOffset + MAX_OFFSET) / K_R;

    for(int i = 0; i < data->length(); i++) {
        int newValue = int((float)data->at(i) * k);
        if(newValue > MAX_BYTE) {
            newValue = MAX_BASE + (newValue % 100) / 2;
        }
        (*data)[i] = newValue;
    }
}

void AudioSource::dataReady()
{
    QByteArray data(reply->readAll());
    QByteArray decoded(data.length() * 2, 0x00);
    ALawDecoder::getInstance()->decode(&data, &decoded);

    if(volumeOffset != 0) {
        applyVolumeOffset(&decoded);
    }

    char* buffer = decoded.data();
    int remaining = decoded.length();

    while(playing && remaining > 0) {
        int written = audio->write(buffer, remaining);
        remaining -= written;
        buffer += written;
        this->msleep(2);
    }
}

void AudioSource::run()
{
    // Setup audio device
    QAudioFormat fmt;
    fmt.setChannels(1);
    fmt.setFrequency(8000);
    fmt.setSampleSize(16);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if(!info.isFormatSupported(fmt)) {
        fmt = info.nearestFormat(fmt);
    }

    audioOut = new QAudioOutput(fmt, this);

    // Start download
    manager = new QNetworkAccessManager();
    QNetworkRequest req(audioUrl);

    reply = manager->get(req);
    connect(reply, SIGNAL(readyRead()), SLOT(dataReady()));

    audio = audioOut->start();
    playing = true;

    this->exec();
}

AudioSource::~AudioSource()
{
    playing = false;

    QNetworkSession session(reply->manager()->configuration());
    session.stop();
    delete reply->manager();
    delete reply;

    this->exit();
}
