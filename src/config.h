#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QHostInfo>
#include "data.h"
#include "periodicrecycler.h"

// Application settings holder
class Config : public QObject
{
    Q_OBJECT
private:
    explicit Config(QObject *parent = 0);
    QString getConfigFilePath();
    static Config *instance;

    QString settingsPath;
    bool editAllowed;
    QList<Data::CameraInfo> cameras;
    int numberOfCols;
    bool showMotionBars;
    Data::RecordMode recordMode;
    int daysToKeep;
    QString dumpDir;
    int postMotionInterval;
    int jpegQuality;
    QByteArray login, passwd;
    QString repairCmd;

    void determineRights();

public:
    // Structure for settings dialog
    struct Settings {
        QString newLogin;
        QString newPasswd;
        QString saveDir;
        Data::RecordMode recordMode;
        int keepPeriod;
        int jpegQuality;
        int postMotionInterval;
        int colsCount;
        bool showMotionBar;
        QString repairCommand;
    };

    static Config* getInstance();
    bool tryFindConfig();
    void loadConfig();
    void updateSources(QList<Data::CameraInfo> &sources);
    void updateSettings(Settings newSettings);
    void saveConfig();

    inline bool getCanEdit() { return this->editAllowed; }
    inline Data::RecordMode getRecordMode() { return recordMode; }
    inline int getDaysToKeepRecords() { return this->daysToKeep; }
    inline int getPostMotionInterval() { return postMotionInterval; }
    inline int getJpegQuality() { return jpegQuality; }
    inline QString getDumpDir() { return dumpDir; }
    inline QList<Data::CameraInfo> *getSources() { return &this->cameras; }
    inline int getColsCount() { return this->numberOfCols; }
    inline int getBarVisibility() { return this->showMotionBars; }
    inline QString getRawLogin() { return QString(this->login); }
    inline QString getRawPassword() { return QString(this->passwd); }
    inline QString getRepairCmd() { return this->repairCmd; }

    QString getAuthHash();

signals:
    void settingsChanged();
    
};

#endif // CONFIG_H
