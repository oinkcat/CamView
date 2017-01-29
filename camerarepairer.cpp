#include "camerarepairer.h"

const int N_A = 111;

CameraRepairer *CameraRepairer::instance;

CameraRepairer *CameraRepairer::getInstance()
{
    if(instance == NULL) {
        instance = new CameraRepairer();
    }
    return instance;
}

CameraRepairer::CameraRepairer(QObject *parent) :
    QObject(parent), targetCamera(NULL)
{
    connect(&watcher, SIGNAL(finished()), SLOT(taskFinished()));
}

QString CameraRepairer::getStatusCodeDescription(int code)
{
    switch(code) {
    case 0:     return QString("repaired");
    case N_A:   return QString("not applicable");
    default:    return QString("error (code %1)").arg(code);
    }
}

void CameraRepairer::taskFinished()
{
    int resultCode = watcher.result();
    emit repairFinished(resultCode);

    CameraWidget *cam = qobject_cast<CameraWidget*>(targetCamera);
    disconnect(cam, SLOT(showRepairStatus(int)));
    this->targetCamera = NULL;
}

int CameraRepairer::startProcess(QString repairCmd)
{
    QProcess repair;
    QStringList cmdAndArgs(repairCmd.split(' '));
    QString cmd = cmdAndArgs[0];
    cmdAndArgs.removeFirst();
    repair.start(cmd, cmdAndArgs);
    repair.waitForFinished();

    return repair.exitCode();
}

void CameraRepairer::startRepair(Data::CameraInfo info)
{
    CameraWidget *cam = qobject_cast<CameraWidget*>(info.widget);
    connect(this, SIGNAL(repairFinished(int)), cam, SLOT(showRepairStatus(int)));
    this->targetCamera = info.widget;

    QUrl camUrl(info.url);
    QString cmd = Config::getInstance()->getRepairCmd().replace("%host", camUrl.host());

    QFuture<int> repairTask = QtConcurrent::run(this, &CameraRepairer::startProcess, cmd);
    watcher.setFuture(repairTask);
}

bool CameraRepairer::canPerformRepair()
{
    QString cmd = Config::getInstance()->getRepairCmd();
    return !(cmd.isEmpty() || watcher.isRunning());
}
