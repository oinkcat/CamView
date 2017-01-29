#ifndef MJPEGHELPERS_H
#define MJPEGHELPERS_H

#include <QObject>
#include <QIODevice>
#include "data.h"

// Some helper functions for MJPEG processing
class MJpegHelpers
{
public:
    static Data::FrameDetails getFrameDetails(QIODevice *source);
    static int getFrameLength(QIODevice *source);
    
private:
    MJpegHelpers();
    static int getIntValueFromHeader(QString headerLine);
};

#endif // MJPEGHELPERS_H
