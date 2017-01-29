#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QFile>
#include <QTimer>
#include <QDateTime>
#include "mjpeghelpers.h"
#include "data.h"

// Widget for playing MJPEG stream
class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();
    void loadFile(QString path);
    int getLength();
    bool isPlaying() { return this->playing; }
    
signals:
    void positionChanged(int position);
    void playingStateChanged(bool playing);
    
protected:
    void paintEvent(QPaintEvent *);

public slots:
    void play();
    void seek(int mtime);
    void singleStep(int direction);

private:
    void buildIndex(QFile *mjpegFile);
    QList<Data::FrameDetails> frameIndex;
    QFile mjpegFile;
    QString filePath;
    bool previewShown;
    int msPosition;
    int currentFrame;
    QImage frame;
    QTimer playTimer;
    bool playing;

private slots:
    void doTimer();
    
};

#endif // PLAYERWIDGET_H
