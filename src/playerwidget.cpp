#include "playerwidget.h"

const int DEFAULT_FRAME_TIME = 100;

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent), msPosition(-1), currentFrame(-1)
{
    this->resize(this->parentWidget()->size());
    connect(&playTimer, SIGNAL(timeout()), SLOT(doTimer()));
}

void PlayerWidget::loadFile(QString path)
{
    if(filePath.length() > 0) {
        mjpegFile.close();
    }

    this->filePath = path;
    this->mjpegFile.setFileName(path);
    mjpegFile.open(QFile::ReadOnly);

    buildIndex(&mjpegFile);
    this->playing = false;
    this->previewShown = false;
    this->currentFrame = -1;
    this->seek(0);
}

void PlayerWidget::buildIndex(QFile *mjpegFile)
{
    bool firstFrameTimeFixed = false;

    frameIndex.clear();
    while(!mjpegFile->atEnd()) {
        Data::FrameDetails details = MJpegHelpers::getFrameDetails(mjpegFile);
        if(!firstFrameTimeFixed) {
            details.timeOffset = 0;
            firstFrameTimeFixed = true;
        }
        frameIndex.append(details);
        mjpegFile->seek(details.fileOffset + details.frameSize);
    }
}

int PlayerWidget::getLength()
{
    int length = -1;
    if(frameIndex.length() > 0) {
        length = frameIndex.last().timeOffset;
    }
    return length;
}

void PlayerWidget::seek(int mtime)
{
    int seekFrame = -1;
    if(mtime > msPosition) {
        // Seek forward
        for(int i = currentFrame + 1; i < frameIndex.length(); i++) {
            if(frameIndex.at(i).timeOffset > mtime) {
                seekFrame = i - 1;
                break;
            }
        }
        if(seekFrame == -1) {
            seekFrame = frameIndex.length() - 1;
        }
    } else if(mtime < msPosition) {
        // Seek backward
        for(int i = currentFrame; i >= 0; i--) {
            if(frameIndex.at(i).timeOffset <= mtime) {
                seekFrame = i;
                break;
            }
        }
        if(seekFrame == -1) {
            seekFrame = 0;
        }
    } else {
        seekFrame = currentFrame;
    }

    if(msPosition != mtime) {
        emit positionChanged(mtime);
        this->msPosition = mtime;
    }

    // Load frame from file if frame changed
    if(seekFrame != currentFrame || !previewShown) {
        if(!previewShown) {
            seekFrame = 0;
            previewShown = true;
        }

        Data::FrameDetails offsets = frameIndex.at(seekFrame);
        mjpegFile.seek(offsets.fileOffset);
        QByteArray imageData = mjpegFile.read(offsets.frameSize);
        frame = QImage::fromData(imageData);

        currentFrame = seekFrame;
        this->update();
    }
}

void PlayerWidget::singleStep(int direction)
{
    int dStep = direction > 0 ? 1 : (direction < 0 ? -1 : 0);
    int newFrame = currentFrame + dStep;

    if(newFrame >= 0 && newFrame < frameIndex.length()) {
        int newFrameTime = frameIndex.at(newFrame).timeOffset;
        seek(newFrameTime);
    }
}

void PlayerWidget::play()
{
    if(!playing) {
        if(msPosition >= frameIndex.at(frameIndex.length() - 1).timeOffset) {
            this->currentFrame = -1;
            this->msPosition = -1;
            this->seek(0);
        }
        playTimer.start(DEFAULT_FRAME_TIME);
        playing = true;
    } else {
        playTimer.stop();
        playing = false;
    }

    emit playingStateChanged(playing);
}

void PlayerWidget::doTimer()
{
    int nextTime = msPosition + DEFAULT_FRAME_TIME;
    int limit = getLength();
    if(nextTime <= limit) {
        this->seek(nextTime);
    } else {
        this->seek(limit);
        playTimer.stop();
        playing = false;
        emit playingStateChanged(false);
    }
}

void PlayerWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(frame.format() != QImage::Format_Invalid) {
        painter.drawImage(this->rect(), frame, frame.rect());
    } else {
        painter.fillRect(this->rect(), Qt::black);
    }

    // Draw the timestamp
    if(msPosition > -1) {
        QFont tsFont(this->font().family(), 24);
        painter.setFont(tsFont);
        painter.setPen(Qt::white);
        painter.setOpacity(0.75);
        QString ts = QString::number(float(msPosition) / 1000, 'f', 3);
        painter.drawText(10, 30, ts);
    }
}

PlayerWidget::~PlayerWidget()
{
    if(mjpegFile.isOpen()) {
        mjpegFile.close();
    }
}
