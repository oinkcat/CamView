#ifndef CAMERAINFODIALOG_H
#define CAMERAINFODIALOG_H

#include <QDialog>
#include "data.h"

namespace Ui {
class CameraInfoDialog;
}

class CameraInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    CameraInfoDialog(Data::CameraInfo info, QWidget *parent = 0);
    ~CameraInfoDialog();
    Data::CameraInfo getNewInfo();

public slots:
    void checkEnteredData();
    
private:
    Ui::CameraInfoDialog *ui;
    void fillCameraInfo(Data::CameraInfo *info);
};

#endif // CAMERAINFODIALOG_H
