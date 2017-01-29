#include "config.h"

const char* CONFIG_FILE = "cam-config.conf";
const char* ACL_FILE = "editors.conf";

Config *Config::instance;

Config *Config::getInstance()
{
    if(!Config::instance) {
        instance = new Config();
    }
    return instance;
}

Config::Config(QObject *parent) :
    QObject(parent), editAllowed(true)
{
}

// Find config file in user directory or %user%/camview dir
bool Config::tryFindConfig()
{
    QString path(QDir::homePath().append('/').append(CONFIG_FILE));
    bool found = QFile::exists(path);
    if(found) {
        this->settingsPath = path;
    } else {
        QString subPath = QString("CamView/").append(CONFIG_FILE);
        path = path.replace(CONFIG_FILE, subPath);
        found = QFile::exists(path);
        if(found) {
            this->settingsPath = path;
        }
    }
    return found;
}

// Determine if user can edit configs
//+by user's hostname
void Config::determineRights()
{
    QFileInfo config(settingsPath);
    QString confDir = config.absoluteDir().path();
    QString aclPath = confDir.append('/').append(ACL_FILE);

    if(QFile::exists(aclPath)) {
        QString thisHost = QHostInfo::localHostName();
        this->editAllowed = false;

        QFile aclFile(aclPath);
        aclFile.open(QFile::ReadOnly);
        while(!aclFile.atEnd()) {
            QString editorHost = aclFile.readLine().trimmed();
            if(thisHost == editorHost) {
                this->editAllowed = true;
            }
        }
        aclFile.close();
    }
}

// Load settings from config file
void Config::loadConfig()
{
    this->determineRights();

    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("display");
    // Number of rows in layout
    this->numberOfCols = settings.value("cols", 3).toInt();

    // Visibility of motion detection bar
    this->showMotionBars = settings.value("motion-bar", 0).toInt() > 0;
    settings.endGroup();

    settings.beginGroup("authentication");
    // Authentication credentials
    this->login = settings.value("login", "-").toByteArray();
    this->passwd = settings.value("password", "-").toByteArray();
    settings.endGroup();

    // Recording options
    settings.beginGroup("recording");
    this->recordMode = (Data::RecordMode)settings.value("mode", 1).toInt();
    this->daysToKeep = settings.value("keep", 3).toInt();
    this->dumpDir = settings.value("directory", "~").toString();
    if(dumpDir == "~") {
        dumpDir = QDir::homePath().append("/dump");
    }
    this->postMotionInterval = settings.value("post-motion").toInt();
    this->jpegQuality = settings.value("quality").toInt();
    settings.endGroup();

    // Repair action
    settings.beginGroup("repair");
    this->repairCmd = settings.value("cmdline").toString();
    settings.endGroup();

    // URL's of cameras
    foreach(QString group, settings.childGroups()) {
        if(group.startsWith("Camera")) {
            settings.beginGroup(group);
            Data::CameraInfo newCamera;
            newCamera.name = settings.value("name").toString();
            newCamera.url = settings.value("url").toString();
            newCamera.audioUrl = settings.value("audio", QString()).toString();
            newCamera.position = settings.value("position").toPoint();

            // Camera's exclusion regions
            foreach(QString keyName, settings.childKeys()) {
                if(keyName.startsWith("exclude-region")) {
                    QRect region = settings.value(keyName).toRect();
                    newCamera.exclusions.append(region);
                }
            }
            cameras.append(newCamera);
            settings.endGroup();
        }
    }
}

// Save to config file
void Config::saveConfig()
{
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.clear();

    settings.setIniCodec("UTF-8");
    settings.beginGroup("display");
    settings.setValue("cols", this->numberOfCols);
    settings.setValue("motion-bar", this->showMotionBars);
    settings.endGroup();

    settings.beginGroup("authentication");
    settings.setValue("login", QString(this->login));
    settings.setValue("password", QString(this->passwd));
    settings.endGroup();

    settings.beginGroup("recording");
    settings.setValue("mode", (int)this->recordMode);
    settings.setValue("keep", this->getDaysToKeepRecords());
    settings.setValue("directory", dumpDir);
    settings.setValue("quality", jpegQuality);
    settings.setValue("post-motion", postMotionInterval);
    settings.endGroup();

    settings.beginGroup("repair");
    settings.setValue("cmdline", repairCmd.trimmed());
    settings.endGroup();

    int camIdx = 0;
    foreach(Data::CameraInfo cam, this->cameras) {
        settings.beginGroup(QString("Camera.%1").arg(QString::number(camIdx)));
        settings.setValue("name", cam.name);
        settings.setValue("url", cam.url);
        if(cam.audioUrl.length() > 0) {
            settings.setValue("audio", cam.audioUrl);
        }
        settings.setValue("position", cam.position);

        int regIdx = 1;
        foreach(QRect region, cam.exclusions) {
            settings.setValue(QString("exclude-region.%1").arg(regIdx), region);
            regIdx++;
        }
        settings.endGroup();
        camIdx++;
    }
}

void Config::updateSources(QList<Data::CameraInfo> &sources)
{
    this->cameras.clear();
    this->cameras = QList<Data::CameraInfo>(sources);
}

// Update settings changed by GUI
void Config::updateSettings(Settings newSettings)
{
    if(newSettings.newLogin.trimmed().length() == 0)
        newSettings.newLogin = "-";
    if(newSettings.newPasswd.trimmed().length() == 0)
        newSettings.newPasswd = "-";

    this->login = QByteArray(newSettings.newLogin.toAscii());
    this->passwd = QByteArray(newSettings.newPasswd.toAscii());
    this->recordMode = newSettings.recordMode;
    this->daysToKeep = newSettings.keepPeriod;
    this->dumpDir = newSettings.saveDir;
    this->jpegQuality = newSettings.jpegQuality;
    this->postMotionInterval = newSettings.postMotionInterval;
    this->numberOfCols = newSettings.colsCount;
    this->showMotionBars = newSettings.showMotionBar;
    this->repairCmd = newSettings.repairCommand;

    PeriodicRecycler::getInstance()->setEnabled(this->recordMode != Data::None);

    emit settingsChanged();
}

QString Config::getAuthHash()
{
    if(login != "-" && passwd != "-") {
        QString authStr = QString("%1:%2").arg(QString(login), QString(passwd));
        QByteArray hash = QByteArray(authStr.toAscii().data()).toBase64();
        return QString(hash);
    } else {
        return QString();
    }
}
