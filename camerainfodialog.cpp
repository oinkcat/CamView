#include "camerainfodialog.h"
#include "ui_camerainfodialog.h"

CameraInfoDialog::CameraInfoDialog(Data::CameraInfo info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraInfoDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QString camName(info.name.length() > 0 ? info.name : "new camera");
    QString title = QString("Settings: ").append(camName);
    this->setWindowTitle(title);
    this->fillCameraInfo(&info);
}

void CameraInfoDialog::fillCameraInfo(Data::CameraInfo *info)
{
    ui->leName->setText(info->name);
    ui->leSourceUrl->setText(info->url);
    ui->leAudioSourceUrl->setText(info->audioUrl);
    checkEnteredData();
}

void CameraInfoDialog::checkEnteredData()
{
    bool okLengths = ui->leName->text().trimmed().length() > 0 &&
                     ui->leSourceUrl->text().trimmed().length() > 0;
    ui->pbOK->setEnabled(okLengths);
}

Data::CameraInfo CameraInfoDialog::getNewInfo()
{
    Data::CameraInfo info;
    info.name = ui->leName->text();
    info.url = ui->leSourceUrl->text();
    info.audioUrl = ui->leAudioSourceUrl->text();

    return info;
}

CameraInfoDialog::~CameraInfoDialog()
{
    delete ui;
}
