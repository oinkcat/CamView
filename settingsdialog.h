#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "config.h"

namespace Ui {
    class SettingsDialog;
}

// GUI for settings
class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    struct SourceSettings {
        QString name;
        QString sourceUrl;
        QString audioUrl;
        Data::CameraInfo *info;

        Data::CameraInfo getInfo()
        {
            Data::CameraInfo info;
            info.name = name;
            info.url = sourceUrl;
            return info;
        }
    };

    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    QList<SourceSettings> *getUpdatedSources() { return &configuringSources; }
    
private:
    Ui::SettingsDialog *ui;
    void showCurrentSettings();
    void fetchCamerasFromConfig(Config *conf);
    inline void showRecordMode(Data::RecordMode mode);
    inline Data::RecordMode getRecordMode();
    QList<SourceSettings> configuringSources;

public slots:
    void toggleQualitySlider(bool value);
    void showCameraItemDetails();
    void toggleAddingMode();
    void saveCameraItem();
    void deleteSelectedItem();
    void toggleSaveButton();
    void saveSettings();
    void showRecordModeDetails();

};

#endif // SETTINGSDIALOG_H
