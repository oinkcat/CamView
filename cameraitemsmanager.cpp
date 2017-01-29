#include "cameraitemsmanager.h"

CameraItemsManager::CameraItemsManager(QList<CameraWidget *> *items, QGridLayout *layout, QObject *parent) :
    QObject(parent), cameras(items), grid(layout)
{
    this->window = qobject_cast<MainWindow*>(parent);
}

void CameraItemsManager::initializeCameras(QList<Data::CameraInfo> *infos)
{
    for(int i = 0; i < infos->length(); i++) {
        Data::CameraInfo *source = const_cast<Data::CameraInfo *>(&(infos->at(i)));
        bool validSource = source->name.trimmed().length() > 0;

        if(validSource) {
            CameraWidget *camera = createCamera(source);
            camera->setProperty("position", source->position);
            camera->start();
            cameras->append(camera);
        }
    }
}

void CameraItemsManager::arrangeCameras()
{
    QList<CameraWidget*> notPlaced;
    int colsCount = Config::getInstance()->getColsCount();

    foreach(CameraWidget* cam, *cameras) {
        QPoint colAndRow = cam->property("position").toPoint();
        if(colAndRow.x() > -1 && colAndRow.x() < colsCount) {
            grid->addWidget(cam, colAndRow.y(), colAndRow.x());
        } else {
            notPlaced.append(cam);
        }
    }

    // Fill free cells
    for(int i = 0; i < grid->rowCount(); i++) {
        for(int j = 0; j < colsCount; j++) {
            QLayoutItem *item = grid->itemAtPosition(i, j);
            bool canPlace = item == NULL;
            if(!canPlace) {
                CameraWidget *testCam = qobject_cast<CameraWidget*>(item->widget());
                if(!testCam->isValid()) {
                    removeCamera(testCam);
                    canPlace = true;
                }
            }
            if(canPlace) {
                CameraWidget *placedItem = NULL;
                if(!notPlaced.isEmpty()) {
                    placedItem = notPlaced.first();
                    placedItem->setProperty("position", QPoint(j, i));
                    notPlaced.removeFirst();
                } else {
                    placedItem = new CameraWidget(new Data::CameraInfo, window);
                    connect(placedItem, SIGNAL(settingsRequested()), window, SLOT(showCameraSettings()));
                }
                grid->addWidget(placedItem, i, j);
            }
        }
    }
}

CameraWidget *CameraItemsManager::createCamera(Data::CameraInfo *info)
{
    CameraWidget *newCamera = new CameraWidget(info, window);
    info->widget = newCamera;

    connect(newCamera, SIGNAL(settingsRequested()), window, SLOT(showCameraSettings()));
    connectCameraSignals(newCamera);

    return newCamera;
}

void CameraItemsManager::connectCameraSignals(CameraWidget *camera)
{
    connect(camera, SIGNAL(doubleClicked()), window, SLOT(expandCamera()));
    connect(camera, SIGNAL(deleteCameraRequested()), window, SLOT(deleteCamera()));
    connect(camera, SIGNAL(repairRequested()), window, SLOT(repairCamera()));
}

void CameraItemsManager::removeCamera(CameraWidget *camera)
{
    grid->removeWidget(camera);
    if(cameras->indexOf(camera) > -1) {
        this->cameras->removeOne(camera);
    }
    camera->close();
    camera->deleteLater();
}

void CameraItemsManager::switchCameraOn(CameraWidget *camera)
{
    camera->start();
    this->cameras->append(camera);
    int idx = grid->indexOf(camera);
    int r, c, d;
    grid->getItemPosition(idx, &r, &c, &d, &d);
    camera->setProperty("position", QPoint(c, r));
    connectCameraSignals(camera);
}

void CameraItemsManager::updateCamerasView(QList<SettingsDialog::SourceSettings> *updatedSources)
{
    bool changed = false;
    QList<Data::CameraInfo> *origSources = Config::getInstance()->getSources();
    QList<const Data::CameraInfo*> existing;
    for(int i = 0; i < origSources->length(); existing.append(&(origSources->at(i++))));

    foreach(SettingsDialog::SourceSettings newSettings, *updatedSources) {
        if(newSettings.info != NULL) {
            // Nothing or camera updated
            CameraWidget *cam = qobject_cast<CameraWidget*>(newSettings.info->widget);
            cam->updateInfo(newSettings.name, newSettings.sourceUrl, newSettings.audioUrl);
            existing.removeOne(newSettings.info);
            changed = true;
        } else {
            // Camera added
            Data::CameraInfo newCameraInfo = newSettings.getInfo();
            CameraWidget *cam = createCamera(&newCameraInfo);
            // Place for arranging algorithm
            cam->setProperty("position", QPoint(-1, -1));
            cam->start();
            this->cameras->append(cam);
            changed = true;
        }
    }

    // Remove deleted cameras
    foreach(const Data::CameraInfo* deleted, existing) {
        CameraWidget *cam = qobject_cast<CameraWidget*>(deleted->widget);
        removeCamera(cam);
        changed = true;
    }

    if(changed) {
        arrangeCameras();
        window->saveVideoSources();
    }
}

void CameraItemsManager::applySettingsToView()
{
    for(int i = 0; i < grid->rowCount(); i++) {
        for(int j = 0; j < grid->columnCount(); j++) {
            QLayoutItem *item = grid->itemAtPosition(i, j);
            if(item != NULL) {
                QWidget *wgtCamera = item->widget();
                grid->removeWidget(wgtCamera);
                wgtCamera->setParent(NULL);
            }
        }
    }
    arrangeCameras();
}
