#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QList>
#include <QGridLayout>
#include <QStackedLayout>
#include <QMouseEvent>
#include "config.h"
#include "camerawidget.h"
#include "settingsdialog.h"
#include "camerainfodialog.h"
#include "playerdialog.h"
#include "apptoolbar.h"
#include "actionmark.h"
#include "audiosource.h"
#include "periodicrecycler.h"
#include "camerarepairer.h"

// Forward declarations
class MainWindow;
class CameraItemsManager;

#include "cameraitemsmanager.h"

// Main application window
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setStyles();
    void attachToolBar();
    CameraWidget *createCameraWidget(Data::CameraInfo *info);
    void removeCameraWidget(CameraWidget *camera);
    void setCameraContextActions(CameraWidget *camera);
    void connectVideoSources();
    void createLayout();
    void arrangeCameras();
    inline bool isCameraExpanded();
    void syncCameras(QList<SettingsDialog::SourceSettings> &updatedSources);
    // Events
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    // Mouse actions
    void rotateArrow(int newX, int newY);
    void replaceCameras(CameraWidget *camera);
    void setMotionIgnoreArea(CameraWidget *camera, int mX, int mY);

    CameraItemsManager *manager;
    AppToolBar *bar;
    QStackedLayout *mainLayout;
    QGridLayout *grid;
    QList<CameraWidget*> cameras;
    AudioSource *audio;
    ActionMark *mark;
    bool isDragging;
    QPoint startPoint;
    QTimer *updater;

public slots:
    // Actions for certain camera
    void showCameraSettings();
    void deleteCamera();
    void repairCamera();
    void expandCamera();
    // Save cameras
    void saveVideoSources();


private slots:
    void minimize() { this->setWindowState(Qt::WindowMinimized); }
    void updateScreen();
    void showPlayer();
    void showSettings();
    void startSourcesUpdate();
    void toggleAudio(bool on);
};

#endif // MAINWINDOW_H
