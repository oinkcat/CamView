#include "motiondetector.h"

const int MAX_MOTION_AMOUNT = 100;
const int CHANGE_THRESHOLD = 100;
const int P_STEP = 2;

MotionDetector::MotionDetector(QObject *parent) :
    QObject(parent)
{
    ready = false;
    alerted = false;
    postMotionRecording = false;
    this->postMotionTimer = new QTimer();
    connect(postMotionTimer, SIGNAL(timeout()), SLOT(motionStopped()));
}

uchar MotionDetector::toGrayscale(QRgb color)
{
    int value = qRed(color) / 3 + qGreen(color) / 2 + qBlue(color) / 5;
    return uchar(value <= 255 ? value : 255);
}

int MotionDetector::getMotion(QImage *newFrame)
{
    QRgb *p0 = (QRgb*)prevFrame.bits();
    QRgb *p1 = (QRgb*)newFrame->bits();
    int ptrEnd = (int)p0 + newFrame->width() * newFrame->height() * 4;

    int amount = 0;
    for(int pIdx = 0; (int)p0 <= ptrEnd; p0 += P_STEP, p1 += P_STEP, pIdx += P_STEP) {
        int x = pIdx % newFrame->width();
        int y = pIdx / newFrame->width();

        bool processPixel = true;
        for(int i = 0; i < this->exclusions.length(); i++) {
            QRect exclusion = this->exclusions.at(i);
            if(exclusion.contains(x, y)) {
                processPixel = false;
                break;
            }
        }

        if(processPixel) {
            uchar gray0 = toGrayscale(*p0);
            uchar gray1 = toGrayscale(*p1);

            int change = abs(gray0 - gray1);
            if(change > CHANGE_THRESHOLD) {
                amount++;
            }
        }
    }

    return amount;
}

void MotionDetector::process(QImage *frame)
{
    if(ready) {
        int changeAmount = getMotion(frame);
        int percent = changeAmount * 100 / MAX_MOTION_AMOUNT;
        percent = percent < 100 ? percent : 100;
        emit motionDetected(percent);

        // Alert if over 90%
        if(percent > 90) {
            // Emit alert signal if not alerted
            if(!alerted) {
                emit motionAlert();
                alerted = true;
            }

            // Stop the overshoot timer on motion
            if(postMotionRecording) {
                postMotionTimer->stop();
                postMotionRecording = false;
            }
        } else if(alerted && !postMotionRecording) {
            int overShootMs = Config::getInstance()->getPostMotionInterval() * 1000;
            postMotionTimer->start(overShootMs);
            postMotionRecording = true;
        }
    }

    prevFrame = *frame;
    ready = true;
}

void MotionDetector::turnOff()
{
    if(this->alerted) {
        this->motionStopped();
    }
}

void MotionDetector::motionStopped()
{
    emit motionCeases();
    postMotionTimer->stop();
    alerted = false;
    postMotionRecording = false;
}
