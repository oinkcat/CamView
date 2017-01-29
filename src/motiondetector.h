#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include "config.h"

// Camera motion detector
class MotionDetector : public QObject
{
    Q_OBJECT
public:
    MotionDetector(QObject *parent = 0);
    void process(QImage *frame);
    void turnOff();
    QList<QRect> *ignoreRegions() { return &this->exclusions; }

signals:
    void motionDetected(int amount);
    void motionAlert();
    void motionCeases();

private:
    inline uchar toGrayscale(QRgb color);
    int getMotion(QImage *newFrame);
    QList<QRect> exclusions;
    bool ready;
    bool alerted;
    bool postMotionRecording;
    QImage prevFrame;
    QTimer *postMotionTimer;

private slots:
    void motionStopped();

};

#endif // MOTIONDETECTOR_H
