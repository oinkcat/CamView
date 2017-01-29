#include "periodicrecycler.h"

const int CHECK_INTERVAL = 30000;
const char *RECYCLE_TIME = "23:00";

PeriodicRecycler *PeriodicRecycler::instance;

PeriodicRecycler::PeriodicRecycler(QObject *) :
    QThread(), enabled(true)
{
    this->moveToThread(this);
}

PeriodicRecycler *PeriodicRecycler::getInstance()
{
    if(PeriodicRecycler::instance == NULL) {
        PeriodicRecycler::instance = new PeriodicRecycler();
    }

    return PeriodicRecycler::instance;
}

void PeriodicRecycler::run()
{
    checker.setInterval(CHECK_INTERVAL);
    connect(&checker, SIGNAL(timeout()), SLOT(checkTime()));
    connect(this, SIGNAL(timeToRecycle()), SLOT(performRecycle()));
    this->exec();
}

void PeriodicRecycler::checkTime()
{
    QTime xTime = QTime::fromString(RECYCLE_TIME, "h:m");
    QTime now = QTime::currentTime();
    now = now.addSecs(-now.second());

    if(now.secsTo(xTime) == 0) {
        emit timeToRecycle();
    }
}

bool PeriodicRecycler::removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
                                                    QDir::System |
                                                    QDir::Hidden  |
                                                    QDir::AllDirs |
                                                    QDir::Files,
                                                    QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

void PeriodicRecycler::performRecycle()
{
    bool internallyInvoked = sender() == this;

    // Only one time a day
    if(internallyInvoked && lastRecycleDate == QDate::currentDate())
        return;

    // Try to recycle old records
    QDir saveDir = QDir(Config::getInstance()->getDumpDir());
    int nDaysToKeep = Config::getInstance()->getDaysToKeepRecords();
    if(saveDir.exists()) {
        foreach(QFileInfo camInfo, saveDir.entryInfoList(QDir::NoDotAndDotDot |
                                                         QDir::Dirs)) {
            QDir camDir(camInfo.absoluteFilePath());
            foreach(QFileInfo dateDir, camDir.entryInfoList(QDir::NoDotAndDotDot |
                                                            QDir::Dirs, QDir::Name)) {
                QDate saveDate = QDate::fromString(dateDir.baseName(), "dd_MM_yyyy");
                if(!saveDate.isValid())
                    continue;

                if(saveDate.daysTo(QDate::currentDate()) > nDaysToKeep) {
                    this->removeDir(dateDir.absoluteFilePath());
                }
            }
        }
    }

    // Remember current date to avoid double recycling
    if(internallyInvoked) {
        lastRecycleDate = QDate::currentDate();
    }
}

void PeriodicRecycler::setEnabled(bool enabled)
{
    if(enabled)
        checker.start();
    else
        checker.stop();
}
