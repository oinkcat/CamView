#ifndef DATA_H
#define DATA_H

#include <QRect>

// Declares data structures used by application
namespace Data {

    // Camera name and url
    struct CameraInfo {
        QString name;
        QString url;
        QString audioUrl;
        QPoint position;
        QObject *widget;
        QList<QRect> exclusions;
    };

    // Various information about frame in record
    struct FrameDetails {
        int timeOffset;
        int fileOffset;
        int frameSize;

    public:
        FrameDetails() : timeOffset(0), fileOffset(0), frameSize(0) {}
    };

    // Recording types
    enum RecordMode { None, Motion };

}

#endif // DATA_H
