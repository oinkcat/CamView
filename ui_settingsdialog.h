/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Sun 3. Apr 22:36:51 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QTabWidget *twTabs;
    QWidget *tab;
    QLabel *label_6;
    QListWidget *lwSources;
    QPushButton *pbAddCamera;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *leTitle;
    QLabel *label_9;
    QLineEdit *leSourceUrl;
    QPushButton *pbDeleteCamera;
    QPushButton *pbSaveCamera;
    QLabel *label_13;
    QLineEdit *leAudioUrl;
    QWidget *tab_4;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *leLogin;
    QLineEdit *lePassword;
    QLabel *label_12;
    QWidget *tab_2;
    QGroupBox *gbRecOptions;
    QLabel *label_3;
    QLineEdit *leDirectory;
    QLabel *label;
    QSpinBox *sbPostMotion;
    QCheckBox *cbDefaultQuality;
    QLabel *label_2;
    QSlider *sldRecordQuality;
    QLabel *label_14;
    QSpinBox *sbKeepPeriod;
    QGroupBox *gbRecMode;
    QRadioButton *rbNoRecord;
    QRadioButton *rbRecOnMotion;
    QWidget *tab_3;
    QGroupBox *gbView;
    QLabel *label_5;
    QCheckBox *cbShowLevel;
    QSpinBox *sbColumns;
    QGroupBox *gbRepair;
    QLabel *label_4;
    QLineEdit *leExtCommand;
    QLabel *label_15;
    QPushButton *pbOK;
    QPushButton *pbCancel;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->setWindowModality(Qt::WindowModal);
        SettingsDialog->resize(442, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/context_actions/res/settings-small.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsDialog->setWindowIcon(icon);
        twTabs = new QTabWidget(SettingsDialog);
        twTabs->setObjectName(QString::fromUtf8("twTabs"));
        twTabs->setGeometry(QRect(10, 10, 421, 421));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 20, 101, 17));
        lwSources = new QListWidget(tab);
        lwSources->setObjectName(QString::fromUtf8("lwSources"));
        lwSources->setGeometry(QRect(10, 50, 191, 291));
        pbAddCamera = new QPushButton(tab);
        pbAddCamera->setObjectName(QString::fromUtf8("pbAddCamera"));
        pbAddCamera->setGeometry(QRect(110, 350, 91, 27));
        pbAddCamera->setAutoDefault(false);
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(210, 20, 181, 17));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(210, 50, 91, 17));
        leTitle = new QLineEdit(tab);
        leTitle->setObjectName(QString::fromUtf8("leTitle"));
        leTitle->setGeometry(QRect(210, 70, 201, 27));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(210, 120, 141, 17));
        leSourceUrl = new QLineEdit(tab);
        leSourceUrl->setObjectName(QString::fromUtf8("leSourceUrl"));
        leSourceUrl->setGeometry(QRect(210, 140, 201, 27));
        pbDeleteCamera = new QPushButton(tab);
        pbDeleteCamera->setObjectName(QString::fromUtf8("pbDeleteCamera"));
        pbDeleteCamera->setEnabled(false);
        pbDeleteCamera->setGeometry(QRect(10, 350, 97, 27));
        pbDeleteCamera->setAutoDefault(false);
        pbSaveCamera = new QPushButton(tab);
        pbSaveCamera->setObjectName(QString::fromUtf8("pbSaveCamera"));
        pbSaveCamera->setEnabled(false);
        pbSaveCamera->setGeometry(QRect(300, 260, 111, 27));
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(210, 190, 141, 17));
        leAudioUrl = new QLineEdit(tab);
        leAudioUrl->setObjectName(QString::fromUtf8("leAudioUrl"));
        leAudioUrl->setGeometry(QRect(210, 210, 201, 27));
        twTabs->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 20, 171, 21));
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 60, 67, 21));
        leLogin = new QLineEdit(tab_4);
        leLogin->setObjectName(QString::fromUtf8("leLogin"));
        leLogin->setGeometry(QRect(200, 20, 201, 27));
        lePassword = new QLineEdit(tab_4);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setGeometry(QRect(200, 60, 201, 27));
        lePassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        label_12 = new QLabel(tab_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 120, 391, 41));
        label_12->setWordWrap(true);
        twTabs->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gbRecOptions = new QGroupBox(tab_2);
        gbRecOptions->setObjectName(QString::fromUtf8("gbRecOptions"));
        gbRecOptions->setGeometry(QRect(10, 120, 401, 271));
        label_3 = new QLabel(gbRecOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 220, 301, 21));
        leDirectory = new QLineEdit(gbRecOptions);
        leDirectory->setObjectName(QString::fromUtf8("leDirectory"));
        leDirectory->setGeometry(QRect(10, 60, 381, 27));
        label = new QLabel(gbRecOptions);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 161, 16));
        sbPostMotion = new QSpinBox(gbRecOptions);
        sbPostMotion->setObjectName(QString::fromUtf8("sbPostMotion"));
        sbPostMotion->setGeometry(QRect(330, 220, 60, 27));
        sbPostMotion->setMaximum(5);
        cbDefaultQuality = new QCheckBox(gbRecOptions);
        cbDefaultQuality->setObjectName(QString::fromUtf8("cbDefaultQuality"));
        cbDefaultQuality->setGeometry(QRect(10, 180, 371, 22));
        label_2 = new QLabel(gbRecOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 150, 171, 17));
        sldRecordQuality = new QSlider(gbRecOptions);
        sldRecordQuality->setObjectName(QString::fromUtf8("sldRecordQuality"));
        sldRecordQuality->setGeometry(QRect(180, 140, 211, 29));
        sldRecordQuality->setMaximum(100);
        sldRecordQuality->setValue(70);
        sldRecordQuality->setOrientation(Qt::Horizontal);
        sldRecordQuality->setTickPosition(QSlider::TicksBelow);
        sldRecordQuality->setTickInterval(10);
        label_14 = new QLabel(gbRecOptions);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 100, 171, 21));
        sbKeepPeriod = new QSpinBox(gbRecOptions);
        sbKeepPeriod->setObjectName(QString::fromUtf8("sbKeepPeriod"));
        sbKeepPeriod->setGeometry(QRect(330, 100, 59, 27));
        sbKeepPeriod->setMinimum(2);
        sbKeepPeriod->setMaximum(30);
        gbRecMode = new QGroupBox(tab_2);
        gbRecMode->setObjectName(QString::fromUtf8("gbRecMode"));
        gbRecMode->setGeometry(QRect(10, 10, 391, 111));
        rbNoRecord = new QRadioButton(gbRecMode);
        rbNoRecord->setObjectName(QString::fromUtf8("rbNoRecord"));
        rbNoRecord->setGeometry(QRect(10, 30, 121, 22));
        rbRecOnMotion = new QRadioButton(gbRecMode);
        rbRecOnMotion->setObjectName(QString::fromUtf8("rbRecOnMotion"));
        rbRecOnMotion->setGeometry(QRect(10, 60, 251, 22));
        twTabs->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gbView = new QGroupBox(tab_3);
        gbView->setObjectName(QString::fromUtf8("gbView"));
        gbView->setGeometry(QRect(10, 10, 401, 121));
        label_5 = new QLabel(gbView);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 40, 181, 21));
        cbShowLevel = new QCheckBox(gbView);
        cbShowLevel->setObjectName(QString::fromUtf8("cbShowLevel"));
        cbShowLevel->setGeometry(QRect(10, 80, 301, 22));
        sbColumns = new QSpinBox(gbView);
        sbColumns->setObjectName(QString::fromUtf8("sbColumns"));
        sbColumns->setGeometry(QRect(330, 40, 59, 27));
        sbColumns->setMinimum(2);
        sbColumns->setMaximum(7);
        gbRepair = new QGroupBox(tab_3);
        gbRepair->setObjectName(QString::fromUtf8("gbRepair"));
        gbRepair->setGeometry(QRect(10, 140, 391, 161));
        gbRepair->setFlat(false);
        gbRepair->setCheckable(false);
        label_4 = new QLabel(gbRepair);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 30, 151, 17));
        leExtCommand = new QLineEdit(gbRepair);
        leExtCommand->setObjectName(QString::fromUtf8("leExtCommand"));
        leExtCommand->setGeometry(QRect(10, 60, 381, 27));
        label_15 = new QLabel(gbRepair);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 90, 381, 51));
        twTabs->addTab(tab_3, QString());
        pbOK = new QPushButton(SettingsDialog);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        pbOK->setGeometry(QRect(350, 440, 81, 27));
        pbCancel = new QPushButton(SettingsDialog);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(260, 440, 81, 27));
        QWidget::setTabOrder(twTabs, lwSources);
        QWidget::setTabOrder(lwSources, pbDeleteCamera);
        QWidget::setTabOrder(pbDeleteCamera, pbAddCamera);
        QWidget::setTabOrder(pbAddCamera, leTitle);
        QWidget::setTabOrder(leTitle, leSourceUrl);
        QWidget::setTabOrder(leSourceUrl, leAudioUrl);
        QWidget::setTabOrder(leAudioUrl, pbSaveCamera);
        QWidget::setTabOrder(pbSaveCamera, rbNoRecord);
        QWidget::setTabOrder(rbNoRecord, rbRecOnMotion);
        QWidget::setTabOrder(rbRecOnMotion, leDirectory);
        QWidget::setTabOrder(leDirectory, sbKeepPeriod);
        QWidget::setTabOrder(sbKeepPeriod, sldRecordQuality);
        QWidget::setTabOrder(sldRecordQuality, cbDefaultQuality);
        QWidget::setTabOrder(cbDefaultQuality, sbPostMotion);
        QWidget::setTabOrder(sbPostMotion, sbColumns);
        QWidget::setTabOrder(sbColumns, cbShowLevel);
        QWidget::setTabOrder(cbShowLevel, leExtCommand);
        QWidget::setTabOrder(leExtCommand, pbOK);
        QWidget::setTabOrder(pbOK, pbCancel);
        QWidget::setTabOrder(pbCancel, leLogin);
        QWidget::setTabOrder(leLogin, lePassword);

        retranslateUi(SettingsDialog);
        QObject::connect(cbDefaultQuality, SIGNAL(toggled(bool)), SettingsDialog, SLOT(toggleQualitySlider(bool)));
        QObject::connect(leTitle, SIGNAL(textChanged(QString)), SettingsDialog, SLOT(toggleSaveButton()));
        QObject::connect(leSourceUrl, SIGNAL(textEdited(QString)), SettingsDialog, SLOT(toggleSaveButton()));
        QObject::connect(SettingsDialog, SIGNAL(accepted()), SettingsDialog, SLOT(saveSettings()));
        QObject::connect(pbCancel, SIGNAL(clicked()), SettingsDialog, SLOT(reject()));
        QObject::connect(pbOK, SIGNAL(clicked()), SettingsDialog, SLOT(accept()));
        QObject::connect(pbAddCamera, SIGNAL(clicked()), SettingsDialog, SLOT(toggleAddingMode()));
        QObject::connect(pbDeleteCamera, SIGNAL(clicked()), SettingsDialog, SLOT(deleteSelectedItem()));
        QObject::connect(lwSources, SIGNAL(itemSelectionChanged()), SettingsDialog, SLOT(showCameraItemDetails()));
        QObject::connect(pbSaveCamera, SIGNAL(clicked()), SettingsDialog, SLOT(saveCameraItem()));
        QObject::connect(rbNoRecord, SIGNAL(clicked()), SettingsDialog, SLOT(showRecordModeDetails()));
        QObject::connect(rbRecOnMotion, SIGNAL(clicked()), SettingsDialog, SLOT(showRecordModeDetails()));

        twTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SettingsDialog", "All cameras:", 0, QApplication::UnicodeUTF8));
        pbAddCamera->setText(QApplication::translate("SettingsDialog", "Add ", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SettingsDialog", "Camera details:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SettingsDialog", "Title", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SettingsDialog", "MJPEG stream URL", 0, QApplication::UnicodeUTF8));
        pbDeleteCamera->setText(QApplication::translate("SettingsDialog", "Remove", 0, QApplication::UnicodeUTF8));
        pbSaveCamera->setText(QApplication::translate("SettingsDialog", "Save", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("SettingsDialog", "Audio source URL", 0, QApplication::UnicodeUTF8));
        twTabs->setTabText(twTabs->indexOf(tab), QApplication::translate("SettingsDialog", "Sources", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("SettingsDialog", "User name:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SettingsDialog", "Password:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">If you have guest access enabled, leave fields above blank</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        twTabs->setTabText(twTabs->indexOf(tab_4), QApplication::translate("SettingsDialog", "Authentication", 0, QApplication::UnicodeUTF8));
        gbRecOptions->setTitle(QApplication::translate("SettingsDialog", "Options", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SettingsDialog", "Record after motion ceases (seconds):", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingsDialog", "Store to following directory:", 0, QApplication::UnicodeUTF8));
        cbDefaultQuality->setText(QApplication::translate("SettingsDialog", "Record directly from source (faster)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SettingsDialog", "MJPEG frame quality:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("SettingsDialog", "Keep recordings upto (days):", 0, QApplication::UnicodeUTF8));
        gbRecMode->setTitle(QApplication::translate("SettingsDialog", "Mode", 0, QApplication::UnicodeUTF8));
        rbNoRecord->setText(QApplication::translate("SettingsDialog", "No recording", 0, QApplication::UnicodeUTF8));
        rbRecOnMotion->setText(QApplication::translate("SettingsDialog", "Record on motion detected", 0, QApplication::UnicodeUTF8));
        twTabs->setTabText(twTabs->indexOf(tab_2), QApplication::translate("SettingsDialog", "Recording", 0, QApplication::UnicodeUTF8));
        gbView->setTitle(QApplication::translate("SettingsDialog", "Grid", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SettingsDialog", "Number of columns:", 0, QApplication::UnicodeUTF8));
        cbShowLevel->setText(QApplication::translate("SettingsDialog", "Show motion level bars", 0, QApplication::UnicodeUTF8));
        gbRepair->setTitle(QApplication::translate("SettingsDialog", "Camera remote reboot/other action", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SettingsDialog", "External command line:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">You can use %host as substitution for source hostname/IP address</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">in command line</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        twTabs->setTabText(twTabs->indexOf(tab_3), QApplication::translate("SettingsDialog", "Miscellaneous", 0, QApplication::UnicodeUTF8));
        pbOK->setText(QApplication::translate("SettingsDialog", "OK", 0, QApplication::UnicodeUTF8));
        pbCancel->setText(QApplication::translate("SettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
