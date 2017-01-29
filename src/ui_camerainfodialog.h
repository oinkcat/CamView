/********************************************************************************
** Form generated from reading UI file 'camerainfodialog.ui'
**
** Created: Sun 3. Apr 22:36:51 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAINFODIALOG_H
#define UI_CAMERAINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CameraInfoDialog
{
public:
    QPushButton *pbCancel;
    QPushButton *pbOK;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *leName;
    QLineEdit *leSourceUrl;
    QLineEdit *leAudioSourceUrl;

    void setupUi(QDialog *CameraInfoDialog)
    {
        if (CameraInfoDialog->objectName().isEmpty())
            CameraInfoDialog->setObjectName(QString::fromUtf8("CameraInfoDialog"));
        CameraInfoDialog->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/context_actions/res/settings-small.png"), QSize(), QIcon::Normal, QIcon::Off);
        CameraInfoDialog->setWindowIcon(icon);
        pbCancel = new QPushButton(CameraInfoDialog);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(210, 250, 81, 27));
        pbOK = new QPushButton(CameraInfoDialog);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        pbOK->setGeometry(QRect(300, 250, 81, 27));
        pbOK->setDefault(true);
        label = new QLabel(CameraInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 71, 21));
        label_2 = new QLabel(CameraInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 131, 21));
        label_3 = new QLabel(CameraInfoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 120, 131, 21));
        leName = new QLineEdit(CameraInfoDialog);
        leName->setObjectName(QString::fromUtf8("leName"));
        leName->setGeometry(QRect(170, 20, 221, 27));
        leSourceUrl = new QLineEdit(CameraInfoDialog);
        leSourceUrl->setObjectName(QString::fromUtf8("leSourceUrl"));
        leSourceUrl->setGeometry(QRect(170, 70, 221, 27));
        leAudioSourceUrl = new QLineEdit(CameraInfoDialog);
        leAudioSourceUrl->setObjectName(QString::fromUtf8("leAudioSourceUrl"));
        leAudioSourceUrl->setGeometry(QRect(170, 120, 221, 27));
        QWidget::setTabOrder(leName, leSourceUrl);
        QWidget::setTabOrder(leSourceUrl, leAudioSourceUrl);
        QWidget::setTabOrder(leAudioSourceUrl, pbCancel);
        QWidget::setTabOrder(pbCancel, pbOK);

        retranslateUi(CameraInfoDialog);
        QObject::connect(pbCancel, SIGNAL(clicked()), CameraInfoDialog, SLOT(reject()));
        QObject::connect(pbOK, SIGNAL(clicked()), CameraInfoDialog, SLOT(accept()));
        QObject::connect(leName, SIGNAL(textChanged(QString)), CameraInfoDialog, SLOT(checkEnteredData()));
        QObject::connect(leSourceUrl, SIGNAL(textChanged(QString)), CameraInfoDialog, SLOT(checkEnteredData()));

        QMetaObject::connectSlotsByName(CameraInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraInfoDialog)
    {
        CameraInfoDialog->setWindowTitle(QApplication::translate("CameraInfoDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pbCancel->setText(QApplication::translate("CameraInfoDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        pbOK->setText(QApplication::translate("CameraInfoDialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CameraInfoDialog", "Title", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CameraInfoDialog", "MJPEG stream URL", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CameraInfoDialog", "Audio stream URL", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraInfoDialog: public Ui_CameraInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAINFODIALOG_H
