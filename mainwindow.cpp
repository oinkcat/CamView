#include "mainwindow.h"

const int UPDATE_INTERVAL = 150;
const char *APP_TITLE = "CamView";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), audio(NULL)
{
    // UI and layout
    this->setCentralWidget(new QWidget(this));
    this->setWindowTitle(APP_TITLE);
    this->createLayout();
    this->attachToolBar();
    this->setStyles();
    this->manager = new CameraItemsManager(&cameras, grid, this);

    manager->initializeCameras(Config::getInstance()->getSources());
    manager->arrangeCameras();

    // Screen update timer
    updater = new QTimer();
    connect(updater, SIGNAL(timeout()), SLOT(updateScreen()));
    updater->start(UPDATE_INTERVAL);

    // Camera action indicator initialization
    this->mark = new ActionMark(this);
    mark->setVisible(false);
    this->isDragging = false;

    // Initialize recycler
    PeriodicRecycler::getInstance()->start();
    bool recycleEnabled = Config::getInstance()->getRecordMode() != Data::None;
    PeriodicRecycler::getInstance()->setEnabled(recycleEnabled);

    connect(Config::getInstance(), SIGNAL(settingsChanged()),
            manager, SLOT(applySettingsToView()));
}

// Set window styles
void MainWindow::setStyles()
{
    Qt::WindowFlags wf = this->windowFlags();
    wf ^= Qt::WindowMaximizeButtonHint;
    wf |= Qt::FramelessWindowHint;
    this->resize(QApplication::desktop()->size());
    this->setWindowFlags(wf);
    this->setWindowState(Qt::WindowFullScreen);
}

// Connect to toolbar signals
void MainWindow::attachToolBar()
{
    bar = new AppToolBar(this);
    this->addToolBar(Qt::RightToolBarArea, bar);
    connect(bar, SIGNAL(closeClicked()), SLOT(close()));
    connect(bar, SIGNAL(minimizeClicked()), SLOT(minimize()));
    connect(bar, SIGNAL(playerClicked()), SLOT(showPlayer()));
    connect(bar, SIGNAL(settingsClicked()), SLOT(showSettings()));
    connect(bar, SIGNAL(audioClicked(bool)), SLOT(toggleAudio(bool)));
}

// Create form layout and grid
void MainWindow::createLayout()
{
    grid = new QGridLayout();
    grid->setSpacing(0);
    grid->setMargin(0);

    QWidget *root = new QWidget(this);
    root->setLayout(grid);
    mainLayout = new QStackedLayout(this);
    mainLayout->addWidget(root);
    this->centralWidget()->setLayout(mainLayout);
}

// Save video sources information to config file
void MainWindow::saveVideoSources()
{
    // Assert is editing enabled
    if(!Config::getInstance()->getCanEdit()) { return; }

    QList<Data::CameraInfo> sourcesToUpdate;
    foreach(CameraWidget *cam, cameras) {
        Data::CameraInfo info = cam->getInfo();
        sourcesToUpdate.append(info);
    }

    Config::getInstance()->updateSources(sourcesToUpdate);
    Config::getInstance()->saveConfig();
}

void MainWindow::updateScreen()
{
    bool isExpandedState = isCameraExpanded();
    foreach(CameraWidget* camera, cameras) {
        if(!isExpandedState || camera == mainLayout->currentWidget()) {
            camera->update();
        }
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    if(this && e->type() == QEvent::WindowStateChange) {
        if(!this->isMinimized()) {
            QTimer::singleShot(100, this, SLOT(showFullScreen()));
            e->accept();
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(Config::getInstance()->getCanEdit()) {
        Config::getInstance()->saveConfig();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    // Assert is editing enabled
    if(!Config::getInstance()->getCanEdit()) { return; }

    bool regionActionsAllowed = Config::getInstance()->getRecordMode() == Data::Motion;

    if(e->button() == Qt::LeftButton) {
        // Allow exclusion region selection only in motion detection mode
        bool allow = !isCameraExpanded() || regionActionsAllowed;

        if(allow) {
            mark->move(e->pos());
            mark->setEnds(e->pos(), e->pos());
            isDragging = true;
            startPoint = e->pos();

            ActionMark::Action action = isCameraExpanded() ? ActionMark::ExcludeArea :
                                                             ActionMark::Move;
            mark->showForAction(action);
        }
    } else if(regionActionsAllowed && e->button() == Qt::RightButton && isCameraExpanded()) {
        CameraWidget *camera = qobject_cast<CameraWidget*>(mainLayout->currentWidget());
        camera->removeExclusionAt(e->pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(isDragging) {
        rotateArrow(e->x(), e->y());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    // Assert is editing enabled
    if(!Config::getInstance()->getCanEdit()) { return; }

    mark->hide();
    isDragging = false;

    CameraWidget *target = qobject_cast<CameraWidget*>(this->childAt(e->pos()));
    if(e->button() == Qt::LeftButton) {
        if(!isCameraExpanded()) {
            replaceCameras(target);

        } else if(target != NULL) {
            setMotionIgnoreArea(target, e->x(), e->y());
        }
    }
}

// Mouse actions
void MainWindow::rotateArrow(int newX, int newY)
{
    int x = qMin<int>(newX, startPoint.x());
    int y = qMin<int>(newY, startPoint.y());
    int w = abs(newX - startPoint.x());
    w = w > 1 ? w : 2;
    int h = abs(newY - startPoint.y());
    h = h > 1 ? h : 2;
    mark->move(x, y);
    mark->resize(w, h);
    mark->setEnds(startPoint, QPoint(newX, newY));
}

void MainWindow::setMotionIgnoreArea(CameraWidget *camera, int mX, int mY)
{
    int startX = qMin<int>(startPoint.x(), mX);
    int startY = qMin<int>(startPoint.y(), mY);

    QPoint relStart(startX, startY);
    QSize lengths(mark->size());
    QPoint relEnd = QPoint(relStart.x() + lengths.width(), relStart.y() + lengths.height());
    if(relEnd.x() - relStart.x() > 10 && relEnd.y() - relStart.y() > 10) {
        camera->addExclusion(QRect(relStart, relEnd));
    }
}

void MainWindow::replaceCameras(CameraWidget *camera)
{
    CameraWidget *source = qobject_cast<CameraWidget*>(this->childAt(startPoint));

    if(source != NULL && camera != NULL && source != camera) {
        int r1, c1, r2, c2, d;
        grid->getItemPosition(grid->indexOf(source), &r1, &c1, &d, &d);
        grid->getItemPosition(grid->indexOf(camera), &r2, &c2, &d, &d);
        grid->removeWidget(source);
        grid->removeWidget(camera);
        grid->addWidget(source, r2, c2);
        grid->addWidget(camera, r1, c1);
        source->setProperty("position", QPoint(c2, r2));
        camera->setProperty("position", QPoint(c1, r1));

        saveVideoSources();
    }
}

// Switch audio source of camera on or off
void MainWindow::toggleAudio(bool on)
{
    if(on) {
        CameraWidget *cam = qobject_cast<CameraWidget*>(mainLayout->currentWidget());
        if(cam->canProvideAudio()) {
            this->audio = new AudioSource(cam->getInfo().audioUrl);
            connect(bar, SIGNAL(volumeChanged(int)), this->audio, SLOT(setVolumeOffset(int)));
            this->audio->start();
        }
    } else if(this->audio != NULL) {
        this->audio->terminate();
    }
}

void MainWindow::showPlayer()
{
    PlayerDialog *wnd = new PlayerDialog(this);
    wnd->show();
}

// Settings management
void MainWindow::showSettings()
{
    if(isCameraExpanded()) {
        expandCamera();
    }

    SettingsDialog *settings = new SettingsDialog(this);
    connect(settings, SIGNAL(accepted()), SLOT(startSourcesUpdate()));
    settings->show();
}

void MainWindow::startSourcesUpdate()
{
    SettingsDialog *dlg = qobject_cast<SettingsDialog*>(sender());
    manager->updateCamerasView(dlg->getUpdatedSources());
}

// REGION: Camera's context menu actions
void MainWindow::showCameraSettings()
{
    CameraWidget *cam = qobject_cast<CameraWidget*>(sender());
    CameraInfoDialog *camSettings = new CameraInfoDialog(cam->getInfo(), this);

    if(camSettings->exec() == QDialog::Accepted) {
        Data::CameraInfo newInfo = camSettings->getNewInfo();
        bool turnedOn = !cam->isValid();
        cam->updateInfo(newInfo.name, newInfo.url, newInfo.audioUrl);

        if(turnedOn) {
            manager->switchCameraOn(cam);
        }

        saveVideoSources();
    }
}

void MainWindow::deleteCamera()
{
    CameraWidget *camera = qobject_cast<CameraWidget*>(sender());
    manager->removeCamera(camera);
    manager->arrangeCameras();
    saveVideoSources();
}

void MainWindow::repairCamera()
{
    CameraWidget *camera = qobject_cast<CameraWidget*>(sender());
    CameraRepairer::getInstance()->startRepair(camera->getInfo());
}

// Expand camera fullscreen or restore to grid via double click
void MainWindow::expandCamera()
{
    CameraWidget *camera = qobject_cast<CameraWidget*>(sender());
    if(camera == NULL) {
        camera = qobject_cast<CameraWidget*>(mainLayout->currentWidget());
    }

    if(!isCameraExpanded()) {
        // Expand camera
        camera->toggleDetectionBar(true);
        camera->setContextMenuPolicy(Qt::NoContextMenu);
        bar->toggleAudioButton(camera->canProvideAudio());

        grid->removeWidget(camera);
        mainLayout->addWidget(camera);
        mainLayout->setCurrentWidget(camera);
    } else {
        // Restore to grid
        camera->toggleDetectionBar(false);
        camera->setContextMenuPolicy(Qt::CustomContextMenu);
        bar->toggleAudioButton(false);
        toggleAudio(false);

        mainLayout->removeWidget(camera);
        mainLayout->setCurrentWidget(grid->parentWidget());
        QPoint pos = camera->property("position").toPoint();
        grid->addWidget(camera, pos.y(), pos.x());
        camera->show();

        saveVideoSources();
    }
}

inline bool MainWindow::isCameraExpanded()
{
    return this->mainLayout->currentWidget() != grid->parentWidget();
}
// ENDREGION


MainWindow::~MainWindow()
{
    delete mark;
    foreach(CameraWidget *camera, cameras) {
        delete camera;
    }
}
