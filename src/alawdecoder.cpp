#include "alawdecoder.h"

ALawDecoder *ALawDecoder::instance;

// Decoder for A-LAW codec
ALawDecoder::ALawDecoder()
{
    initializeMapping();
}

void ALawDecoder::initializeMapping()
{
    for(int i = 0; i <= 0xff; i++) {
        int alaw = i ^ 0xD5;

        int sign = alaw & 0x80;
        int exponent = (alaw & 0x70) >> 4;
        int data = alaw & 0x0f;

        data <<= 4;
        data += 8;

        if (exponent != 0)
            data += 0x100;
        if (exponent > 1)
            data <<= (exponent - 1);

        map[i] = short(sign == 0 ? data : -data);
    }
}

void ALawDecoder::decode(QByteArray *data, QByteArray *out)
{
    for(int i = 0; i < data->length(); i++) {
        unsigned char idx = data->at(i);
        short mapped = map[idx];
        (*out)[i * 2] = mapped & 0xff;
        (*out)[i * 2 + 1] = (mapped >> 8) & 0xff;
    }
}

ALawDecoder *ALawDecoder::getInstance()
{
    if(!ALawDecoder::instance) {
        instance = new ALawDecoder();
    }

    return instance;
}
