#include "camerawidget.h"

const int BAR_HEIGHT = 5;
const int MAX_IMG_WIDTH = 1000;
const int SHOW_HOST_ZONE = 32;
const int REPAIR_STATUS_INTERVAL = 2000;

CameraWidget::CameraWidget(Data::CameraInfo *info, QWidget *parent) :
    QWidget(parent), source(NULL), detector(NULL), recorder(NULL),
    name(info->name), frameReady(false), sourceError(false),
    showHost(false), lastRepairStatus(-1)
{
    if(isValid()) {
        createUtilityObjects(info->name, info->url, info->audioUrl);

        foreach(QRect exclusion, info->exclusions) {
            detector->ignoreRegions()->append(exclusion);
        }
    }

    // Config based options
    this->forceShowBar = Config::getInstance()->getBarVisibility();
    // Context menu
    if(Config::getInstance()->getCanEdit()) {
        this->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(showContextMenu(QPoint)));
    }
}

// Prepare camera source, recorder and motion detector
void CameraWidget::createUtilityObjects(QString name, QString url, QString audioUrl)
{
    this->setMouseTracking(true);
    this->audioUrl = audioUrl;
    this->source = new MJPegSource(url);
    this->recorder = new MJpegDumper(name);
    this->detector = new MotionDetector;
}

// Set event handlers and start activity
void CameraWidget::start()
{
    connect(source, SIGNAL(frameReceived(QByteArray*)), SLOT(imageLoaded(QByteArray*)));
    connect(source, SIGNAL(error()), SLOT(sourceFailed()));
    source->start();
    source->toggleFrameSkip(true);

    this->motionPercent = 0;
    connect(detector, SIGNAL(motionDetected(int)), SLOT(updateMotion(int)));
    connect(detector, SIGNAL(motionAlert()), SLOT(startRecording()));
    connect(detector, SIGNAL(motionQuiet()), SLOT(stopRecording()));

    this->recording = false;
    recControlTimer = new QTimer();
    connect(recControlTimer, SIGNAL(timeout()), SLOT(controlRecord()));
}

// Update camera name or source url if changed
void CameraWidget::updateInfo(QString newName, QString newSourceUrl, QString newAudioUrl)
{
    // Create utility objects if camera previously was off
    if(!isValid()) {
        createUtilityObjects(newName, newSourceUrl, newAudioUrl);
    }

    this->audioUrl = newAudioUrl;
    if(this->name != newName) {
        this->name = newName;
        recorder->updateSourceName(newName);
    }
    if(source->getUrl() != newSourceUrl) {
        source->updateUrl(newSourceUrl);
    }
}

// Get CameraInfo information for this camera
Data::CameraInfo CameraWidget::getInfo()
{
    Data::CameraInfo myInfo;
    myInfo.name = this->name;
    myInfo.url = source != NULL ? source->getUrl() : "";
    myInfo.audioUrl = source != NULL ? this->audioUrl : "";
    myInfo.position = this->property("position").toPoint();
    myInfo.widget = this;
    if(this->detector != NULL) {
        myInfo.exclusions = *this->detector->ignoreRegions();
    }
    return myInfo;
}

void CameraWidget::imageLoaded(QByteArray *data)
{
    QImage loadedFrame = QImage::fromData(*data, "JPG");
    if(!loadedFrame.isNull() && loadedFrame.format() != QImage::Format_Invalid &&
            loadedFrame.width() < MAX_IMG_WIDTH) {
        frame = loadedFrame;
        frameReady = true;

        // Motion detection (if set)
        if(isMotionDetecting()) {
            detector->process(&frame);
        } else {
            detector->turnOff();
        }

        // Dump frame if recording
        if(recording) {
            recorder->dumpFrameData(data);
        }
    }
}

// Get ratio for fullscreen camera view
QSizeF CameraWidget::getImageScalingRatios()
{
    float horizRatio = float(frame.width()) / this->width();
    float vertRatio = float(frame.height()) / this->height();
    return QSizeF(horizRatio, vertRatio);
}

void CameraWidget::updateMotion(int percent)
{
    this->motionPercent = percent;
}

// Add rectangle exclusion region for motion detection
void CameraWidget::addExclusion(QRect region)
{
    QSizeF ks = getImageScalingRatios();
    QRect scaledRect = QRect(int(region.left() * ks.width()),
                             int(region.top() * ks.height()),
                             int(region.width() * ks.width()),
                             int(region.height() * ks.height()));
    detector->ignoreRegions()->append(scaledRect);
}

// Remove exclusion region at given point
void CameraWidget::removeExclusionAt(QPoint point)
{
    QSizeF ks = getImageScalingRatios();
    QPoint scaledPoint(int(point.x() * ks.width()),
                       int(point.y() * ks.height()));
    int i = 0;
    foreach(QRect region, *detector->ignoreRegions()) {
        if(region.contains(scaledPoint)) {
            detector->ignoreRegions()->removeAt(i);
            break;
        }
        i++;
    }
}

void CameraWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClicked();
}

void CameraWidget::mouseMoveEvent(QMouseEvent *event)
{
    showHost = event->y() < SHOW_HOST_ZONE;
    event->ignore();
}

void CameraWidget::leaveEvent(QEvent *)
{
    showHost = false;
}

void CameraWidget::showContextMenu(QPoint p)
{
    QPoint globalPos = this->mapToGlobal(p);

    QMenu ctxMenu;
    QIcon setIcon(":/new/context_actions/res/settings-small.png");
    QAction actSettings(setIcon,
                        tr("&Settings"), this);
    actSettings.setIconVisibleInMenu(true);
    connect(&actSettings, SIGNAL(triggered()), SIGNAL(settingsRequested()));
    ctxMenu.addAction(&actSettings);

    QAction actRemove(QIcon(":/new/context_actions/res/delete.png"),
                      tr("&Remove"), this);
    actRemove.setEnabled(isValid());
    actRemove.setIconVisibleInMenu(true);
    connect(&actRemove, SIGNAL(triggered()), SIGNAL(deleteCameraRequested()));
    ctxMenu.addAction(&actRemove);

    QAction actRepair(QIcon(":/new/context_actions/res/repair.png"),
                      tr("Re&pair"), this);
    bool canRepair = CameraRepairer::getInstance()->canPerformRepair();
    actRepair.setEnabled(isValid() && canRepair);
    actRepair.setIconVisibleInMenu(true);
    connect(&actRepair, SIGNAL(triggered()), SIGNAL(repairRequested()));
    ctxMenu.addAction(&actRepair);

    ctxMenu.exec(globalPos);
}

void CameraWidget::paintEvent(QPaintEvent*)
{
    const int REC_RADIUS = 12;

    QPainter painter(this);
    painter.setBrush(Qt::SolidPattern);

    QString statusDesc;
    if(source != NULL) {
        statusDesc = source->getStatusDescription();
        if(source->ok()) {
            this->sourceError = false;
        }
    }

    // Camera image
    if(frameReady) {
        bool inDetectionMode = isMotionDetecting();
        bool barVisible = Config::getInstance()->getBarVisibility();
        bool drawMotionParts = inDetectionMode && (barVisible || forceShowBar);
        QRect destRect = this->rect();

        if(drawMotionParts) {
            destRect.adjust(0, 0, 0, -BAR_HEIGHT);
        }
        painter.drawImage(destRect, frame, frame.rect());

        // Detection bar and exclusion regions
        if(drawMotionParts) {
            drawBarAndRegions(painter);
        }

        // Show recording state
        if(recording && recordMarkShown) {
            painter.setPen(Qt::red);
            painter.setBrush(QBrush(Qt::red));
            QPoint markCenter(this->width() - REC_RADIUS - 10, REC_RADIUS + 10);
            painter.drawEllipse(markCenter, REC_RADIUS, REC_RADIUS);
        }
    } else {
        painter.fillRect(this->rect(), Qt::black);
    }

    // Error mark
    if(this->sourceError) {
        painter.setPen(QPen(QBrush(Qt::red), 2));
        if(source->getStatus() != MJPegSource::Rejected) {
            painter.drawLine(this->width() - REC_RADIUS * 2 - 10, 10,
                             this->width() - 10, REC_RADIUS * 2 + 10);
            painter.drawLine(this->width() - REC_RADIUS * 2 - 10, REC_RADIUS * 2 + 10,
                             this->width() - 10, 10);
        } else {
            QPoint markCenter(this->width() - REC_RADIUS - 10, REC_RADIUS + 10);
            painter.drawEllipse(markCenter, REC_RADIUS, REC_RADIUS);
        }
    }

    bool isRepairing = CameraRepairer::getInstance()->getTargetCamera() == this;
    // Camera name
    if(isValid()) {
        drawNameAndStatus(painter, statusDesc, isRepairing);
    }

    // Bounding rectangle
    painter.setPen(isRepairing || lastRepairStatus > -1 ? Qt::yellow : Qt::darkGray);
    painter.setBrush(Qt::NoBrush);
    QRect bounds(this->rect());
    bounds.adjust(0, 0, -1, -1);
    painter.drawRect(bounds);
}

void CameraWidget::drawBarAndRegions(QPainter &painter)
{
    int barWidth = motionPercent * this->width() / 100;
    int barY = this->height() - BAR_HEIGHT;
    painter.fillRect(0, barY, barWidth, BAR_HEIGHT, Qt::red);
    painter.fillRect(barWidth + 1, barY, this->width(), BAR_HEIGHT, Qt::black);

    // Draw detection exclusion regions
    if(detector->ignoreRegions()->length() > 0) {
        QSizeF ks = getImageScalingRatios();
        painter.setPen(Qt::red);
        foreach(QRect exc, *detector->ignoreRegions()) {
            float rx = exc.x() / ks.width(),
                  ry = exc.y() / ks.height();
            float rw = exc.width() / ks.width(),
                  rh = exc.height() / ks.height();
            painter.setOpacity(0.15);
            painter.setBrush(Qt::red);
            painter.drawRect(QRectF(rx, ry, rw, rh));
            painter.setOpacity(1);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(QRectF(rx, ry, rw, rh));
            painter.drawLine(QPointF(rx, ry), QPointF(rx + rw, ry + rh));
            painter.drawLine(QPointF(rx, ry + rh), QPointF(rx + rw, ry));
        }
    }
}

void CameraWidget::drawNameAndStatus(QPainter &painter, QString addStatus, bool repairing)
{
    // Name or host
    QString infoString = this->name;
    if(!forceShowBar && showHost) {
        QUrl mjpgUrl(source->getUrl());
        infoString = mjpgUrl.host();
    }

    if(forceShowBar) {
        infoString = infoString.append(" (")
                               .append(source->getUrl())
                               .append(")");
    }

    // Status
    if(addStatus.length() > 0) {
        infoString = infoString.append(" - ").append(addStatus);
    }

    drawMessage(painter, 0, infoString);
    if(repairing) {
        drawMessage(painter, 1, "in progress...");
    } else if(lastRepairStatus > -1) {
        QString status = CameraRepairer::getStatusCodeDescription(lastRepairStatus);
        drawMessage(painter, 1, status);
    }
}

void CameraWidget::drawMessage(QPainter &painter, int row, QString text)
{
    const int TEXT_PAD = 4;

    QFontMetrics fm(painter.font());
    int nameWidth = fm.width(text);
    int nameHeight = fm.height();
    QColor nameBgColor(qRgba(0, 0, 0, 100));
    painter.setPen(nameBgColor);
    painter.setBrush(QBrush(nameBgColor));
    painter.setOpacity(0.75);
    int y = row * nameHeight;
    painter.drawRect(0, y, nameWidth + TEXT_PAD, y + nameHeight + TEXT_PAD);
    painter.setPen(Qt::white);
    painter.drawText(TEXT_PAD / 2, y + nameHeight, text);
    painter.setOpacity(1);
}

// Start recording stream on motion detected
void CameraWidget::startRecording()
{
    source->toggleFrameSkip(false);
    recorder->beginDump();
    recording = recordMarkShown = true;
    recControlTimer->start(1000);
}

// Stop recording
void CameraWidget::stopRecording()
{
    source->toggleFrameSkip(true);
    recorder->endDump();
    recording = recordMarkShown = false;
    recControlTimer->stop();
}

// Camera repair is finished
void CameraWidget::showRepairStatus(int statusCode)
{
    this->lastRepairStatus = statusCode;
    QTimer::singleShot(REPAIR_STATUS_INTERVAL, this, SLOT(clearRepairStatus()));
}

void CameraWidget::sourceFailed()
{
    if(recording) {
        stopRecording();
    }
    sourceError = true;
    frameReady = false;
}

void CameraWidget::controlRecord()
{
    recordMarkShown ^= true;
}

CameraWidget::~CameraWidget()
{
    delete recorder;
}
