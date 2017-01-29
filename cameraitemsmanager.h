#ifndef CAMERAITEMSMANAGER_H
#define CAMERAITEMSMANAGER_H

#include <QObject>
#include <QGridLayout>
#include "camerawidget.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include "data.h"
#include "config.h"

// Manages creation, removing and arranging of camera widgets
class CameraItemsManager : public QObject
{
    Q_OBJECT

private:
    // Pointers to parent object's item containers
    QList<CameraWidget*> *cameras;
    QGridLayout *grid;
    MainWindow *window;

public:
    CameraItemsManager(QList<CameraWidget*> *items, QGridLayout *layout, QObject *parent = 0);
    CameraWidget *createCamera(Data::CameraInfo *info);
    void connectCameraSignals(CameraWidget *camera);
    void removeCamera(CameraWidget *camera);
    void switchCameraOn(CameraWidget *camera);

    void initializeCameras(QList<Data::CameraInfo> *infos);
    void updateCamerasView(QList<SettingsDialog::SourceSettings> *updatedSources);
    
signals:
    
public slots:
    void arrangeCameras();
    void applySettingsToView();
    
};

#endif // CAMERAITEMSMANAGER_H
