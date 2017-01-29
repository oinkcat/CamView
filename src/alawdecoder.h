#ifndef ALAWDECODER_H
#define ALAWDECODER_H

#include <QObject>
#include <QByteArray>

class ALawDecoder
{
public:
    static ALawDecoder *getInstance();
    void decode(QByteArray *data, QByteArray *out);

private:
    ALawDecoder();
    void initializeMapping();

    static ALawDecoder *instance;
    short map[256];

};

#endif // ALAWDECODER_H
