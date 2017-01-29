#include "mjpeghelpers.h"

const char* LENGTH_HEADER = "content-length";
const char* TIME_HEADER = "x-timestamp";

int MJpegHelpers::getFrameLength(QIODevice *source)
{
    return getFrameDetails(source).frameSize;
}

int MJpegHelpers::getIntValueFromHeader(QString headerLine)
{
    int off = headerLine.length() - headerLine.indexOf(' ');
    int value = headerLine.right(off).toInt();
    return value;
}

// Get frame size, timestamp and byte offset from beginning of file
Data::FrameDetails MJpegHelpers::getFrameDetails(QIODevice *source)
{
    Data::FrameDetails details;

    QString line = NULL;
    do {
        // Read MJPEG headers
        line = source->readLine().toLower();
        if(line.startsWith(LENGTH_HEADER)) {
            details.frameSize = getIntValueFromHeader(line);
        } else if(line.startsWith(TIME_HEADER)) {
            details.timeOffset = getIntValueFromHeader(line);
        }
    }
    while(line.trimmed().length() != 0);
    details.fileOffset = source->pos();

    return details;
}
