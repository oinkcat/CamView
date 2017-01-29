#ifndef CAMERAREPAIRER_H
#define CAMERAREPAIRER_H

#include <QObject>
#include <QFuture>
#include <QtConcurrentRun>
#include <QFutureWatcher>
#include <QUrl>
#include <QProcess>
#include "camerawidget.h"
#include "config.h"
#include "data.h"

// Performs camera reboot/repair/other command in separate thread
class CameraRepairer : public QObject
{
    Q_OBJECT
private:
    explicit CameraRepairer(QObject *parent = 0);
    int startProcess(QString repairCmd);
    static CameraRepairer *instance;
    QFutureWatcher<int> watcher;
    QObject *targetCamera;

public:
    static CameraRepairer *getInstance();
    static QString getStatusCodeDescription(int code);
    bool canPerformRepair();
    void startRepair(Data::CameraInfo info);
    inline QObject *getTargetCamera() { return this->targetCamera; }
    
signals:
    void repairFinished(int);

private slots:
    void taskFinished();

public slots:
    
};

#endif // CAMERAREPAIRER_H
