#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    showCurrentSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showRecordModeDetails()
{
    ui->gbRecOptions->setEnabled(ui->rbRecOnMotion->isChecked());
}

// Display recording mode by radio buttons
void SettingsDialog::showRecordMode(Data::RecordMode mode)
{
    QRadioButton* selected = mode == Data::None ?
                ui->rbNoRecord :
                ui->rbRecOnMotion;

    ui->gbRecOptions->setEnabled(mode != Data::None);
    selected->setChecked(true);
}

// Get recording mode displayed by radio buttons
Data::RecordMode SettingsDialog::getRecordMode()
{
    Data::RecordMode mode = ui->rbNoRecord->isChecked() ?
                    Data::None :
                    Data::Motion;
    return mode;
}


void SettingsDialog::showCurrentSettings()
{
    Config *conf = Config::getInstance();

    // Cameras
    fetchCamerasFromConfig(conf);

    // Recording
    showRecordMode(conf->getRecordMode());
    ui->sbKeepPeriod->setValue(conf->getDaysToKeepRecords());
    ui->leDirectory->setText(conf->getDumpDir());
    int quality = conf->getJpegQuality();
    ui->cbDefaultQuality->setChecked(quality == -1);
    if(quality > -1) {
        ui->sldRecordQuality->setValue(quality);
    }
    toggleQualitySlider(ui->cbDefaultQuality->isChecked());
    ui->sbPostMotion->setValue(conf->getPostMotionInterval());

    // Login and password
    QString login = conf->getRawLogin() != "-" ? conf->getRawLogin() : QString();
    QString passwd = conf->getRawPassword() != "-" ? conf->getRawPassword() : QString();
    ui->leLogin->setText(login);
    ui->lePassword->setText(passwd);

    // Advanced
    ui->sbColumns->setValue(conf->getColsCount());
    ui->cbShowLevel->setChecked(conf->getBarVisibility());
    ui->leExtCommand->setText(conf->getRepairCmd());
}

void SettingsDialog::fetchCamerasFromConfig(Config *conf)
{
    QList<Data::CameraInfo> *sources = conf->getSources();
    for (int i = 0; i < sources->length(); i++) {
        Data::CameraInfo *cam = const_cast<Data::CameraInfo *>(&(sources->at(i)));
        SourceSettings aSource;
        aSource.name = cam->name;
        aSource.sourceUrl = cam->url;
        aSource.audioUrl = cam->audioUrl;
        aSource.info = cam;
        configuringSources.append(aSource);

        ui->lwSources->addItem(aSource.name);
    }
}

void SettingsDialog::toggleQualitySlider(bool value)
{
    ui->sldRecordQuality->setEnabled(!value);
}

void SettingsDialog::toggleSaveButton()
{
    ui->pbSaveCamera->setEnabled(ui->leTitle->text().length() > 0 &&
                                 ui->leSourceUrl->text().length() > 0);
}

void SettingsDialog::toggleAddingMode()
{
    ui->lwSources->clearSelection();
    ui->leTitle->clear();
    ui->leSourceUrl->clear();
    ui->leAudioUrl->clear();
    ui->pbDeleteCamera->setEnabled(false);
}

// Fill information fields and enable buttons
void SettingsDialog::showCameraItemDetails()
{
    SourceSettings source = configuringSources.at(ui->lwSources->currentRow());
    ui->leTitle->setText(source.name);
    ui->leSourceUrl->setText(source.sourceUrl);
    ui->leAudioUrl->setText(source.audioUrl);
    ui->pbDeleteCamera->setEnabled(true);
    ui->pbSaveCamera->setEnabled(true);
}

void SettingsDialog::saveCameraItem()
{
    if(ui->lwSources->selectedItems().length() == 0) {
        // Add item
        SourceSettings addedCamera;
        addedCamera.name = ui->leTitle->text();
        addedCamera.sourceUrl = ui->leSourceUrl->text();
        addedCamera.audioUrl = ui->leAudioUrl->text();
        addedCamera.info = NULL;
        configuringSources.append(addedCamera);

        ui->lwSources->addItem(addedCamera.name);
    } else {
        // Edit item
        SourceSettings *editingSource = const_cast<SourceSettings*>(
                    &configuringSources.at(ui->lwSources->currentRow()));
        editingSource->name = ui->leTitle->text();
        editingSource->sourceUrl = ui->leSourceUrl->text();
        editingSource->audioUrl = ui->leAudioUrl->text();
        ui->lwSources->currentItem()->setText(editingSource->name);
    }
}

// Remove source from list
void SettingsDialog::deleteSelectedItem()
{
    int idx = ui->lwSources->currentRow();
    configuringSources.removeAt(idx);

    ui->lwSources->takeItem(idx);
    toggleAddingMode();
}

void SettingsDialog::saveSettings()
{
    Config::Settings newSettings;
    newSettings.newLogin = ui->leLogin->text();
    newSettings.newPasswd = ui->lePassword->text();
    newSettings.recordMode = getRecordMode();
    newSettings.keepPeriod = ui->sbKeepPeriod->value();
    newSettings.saveDir = ui->leDirectory->text();
    int qual = ui->cbDefaultQuality->isChecked() ? -1 : ui->sldRecordQuality->value();
    newSettings.jpegQuality = qual;
    newSettings.postMotionInterval = ui->sbPostMotion->value();
    newSettings.colsCount = ui->sbColumns->value();
    newSettings.showMotionBar = ui->cbShowLevel->isChecked();
    newSettings.repairCommand = ui->leExtCommand->text();
    Config::getInstance()->updateSettings(newSettings);
    Config::getInstance()->saveConfig();
}
