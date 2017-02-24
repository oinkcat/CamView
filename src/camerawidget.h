#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QImageReader>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QMenu>
#include "motiondetector.h"
#include "mjpegdumper.h"
#include "mjpegsource.h"
#include "alawdecoder.h"
#include "data.h"
#include "camerarepairer.h"

// Widget with associated video source, player and recorder
class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(Data::CameraInfo *info, QWidget *parent);
    ~CameraWidget();
    void start();
    void updateInfo(QString newName, QString newSourceUrl, QString newAudioUrl);
    void toggleDetectionBar(bool visible) { this->forceShowBar = visible; }
    Data::CameraInfo getInfo();
    void addExclusion(QRect region);
    void removeExclusionAt(QPoint point);

    inline bool canProvideAudio() { return source && frameReady && audioUrl.length() > 0; }
    inline bool isValid() { return name.length() > 0; }
    
signals:

private slots:
    void imageLoaded(QByteArray &data);
    void updateMotion(int percent);
    void startRecording();
    void sourceFailed();
    void controlRecord();
    void showContextMenu(QPoint p);

    void clearRepairStatus() { this->lastRepairStatus = -1; }
    
signals:
    void doubleClicked();
    void settingsRequested();
    void deleteCameraRequested();
    void repairRequested();

public slots:
    void stopRecording();
    void showRepairStatus(int statusCode);

private:
    inline QSizeF getImageScalingRatios();
    void createUtilityObjects(QString name, QString url, QString audioUrl);
    void drawBarAndRegions(QPainter &painter);
    void drawNameAndStatus(QPainter &painter, QString addStatus, bool repairing);
    void drawMessage(QPainter &painter, int row, QString text);

    inline bool isMotionDetecting() {
        return Config::getInstance()->getRecordMode() == Data::Motion;
    }

    QString name;
    QString audioUrl;
    bool showHost;
    bool frameReady;
    QImage frame;
    int lastRepairStatus;
    bool sourceError;

    // MJPEG source
    MJPegSource *source;

    // Motion detection related
    MotionDetector *detector;
    int motionPercent;
    bool forceShowBar;

    // Video recording related
    MJpegDumper *recorder;
    bool recording;
    bool recordMarkShown;
    QTimer *recControlTimer;
    
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

};

#endif // CAMERAWIDGET_H
