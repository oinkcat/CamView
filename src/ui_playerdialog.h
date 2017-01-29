/********************************************************************************
** Form generated from reading UI file 'playerdialog.ui'
**
** Created: Sun 3. Apr 22:36:51 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERDIALOG_H
#define UI_PLAYERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *lytMain;
    QVBoxLayout *lytLeft;
    QFrame *frmImage;
    QSlider *sldPosition;
    QHBoxLayout *lytControls;
    QPushButton *pbPrev;
    QPushButton *pbBack;
    QPushButton *pbPlay;
    QPushButton *pbForward;
    QPushButton *pbNext;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSetStart;
    QPushButton *pbSetEnd;
    QPushButton *pbSave;
    QLabel *lblStatus;
    QVBoxLayout *lytRight;
    QLabel *label;
    QComboBox *cbCameras;
    QLabel *label_2;
    QComboBox *cbDates;
    QLabel *label_3;
    QListWidget *lstRecords;
    QPushButton *pbClose;

    void setupUi(QDialog *PlayerDialog)
    {
        if (PlayerDialog->objectName().isEmpty())
            PlayerDialog->setObjectName(QString::fromUtf8("PlayerDialog"));
        PlayerDialog->setWindowModality(Qt::WindowModal);
        PlayerDialog->setEnabled(true);
        PlayerDialog->resize(800, 619);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlayerDialog->sizePolicy().hasHeightForWidth());
        PlayerDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/controls/res/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        PlayerDialog->setWindowIcon(icon);
        horizontalLayoutWidget = new QWidget(PlayerDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 781, 601));
        lytMain = new QHBoxLayout(horizontalLayoutWidget);
        lytMain->setObjectName(QString::fromUtf8("lytMain"));
        lytMain->setContentsMargins(0, 0, 0, 0);
        lytLeft = new QVBoxLayout();
        lytLeft->setObjectName(QString::fromUtf8("lytLeft"));
        frmImage = new QFrame(horizontalLayoutWidget);
        frmImage->setObjectName(QString::fromUtf8("frmImage"));
        sizePolicy.setHeightForWidth(frmImage->sizePolicy().hasHeightForWidth());
        frmImage->setSizePolicy(sizePolicy);
        frmImage->setMinimumSize(QSize(640, 480));
        frmImage->setFrameShape(QFrame::Box);
        frmImage->setFrameShadow(QFrame::Sunken);

        lytLeft->addWidget(frmImage);

        sldPosition = new QSlider(horizontalLayoutWidget);
        sldPosition->setObjectName(QString::fromUtf8("sldPosition"));
        sldPosition->setEnabled(false);
        sldPosition->setMaximum(5000);
        sldPosition->setSingleStep(100);
        sldPosition->setPageStep(100);
        sldPosition->setOrientation(Qt::Horizontal);
        sldPosition->setInvertedAppearance(false);
        sldPosition->setInvertedControls(false);
        sldPosition->setTickPosition(QSlider::NoTicks);

        lytLeft->addWidget(sldPosition);

        lytControls = new QHBoxLayout();
        lytControls->setObjectName(QString::fromUtf8("lytControls"));
        pbPrev = new QPushButton(horizontalLayoutWidget);
        pbPrev->setObjectName(QString::fromUtf8("pbPrev"));
        pbPrev->setEnabled(false);
        pbPrev->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/player_controls/res/player_start.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPrev->setIcon(icon1);
        pbPrev->setCheckable(false);

        lytControls->addWidget(pbPrev);

        pbBack = new QPushButton(horizontalLayoutWidget);
        pbBack->setObjectName(QString::fromUtf8("pbBack"));
        pbBack->setEnabled(false);
        pbBack->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/player_controls/res/player_rev.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbBack->setIcon(icon2);
        pbBack->setFlat(false);

        lytControls->addWidget(pbBack);

        pbPlay = new QPushButton(horizontalLayoutWidget);
        pbPlay->setObjectName(QString::fromUtf8("pbPlay"));
        pbPlay->setEnabled(false);
        pbPlay->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/player_controls/res/player_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPlay->setIcon(icon3);

        lytControls->addWidget(pbPlay);

        pbForward = new QPushButton(horizontalLayoutWidget);
        pbForward->setObjectName(QString::fromUtf8("pbForward"));
        pbForward->setEnabled(false);
        pbForward->setFocusPolicy(Qt::NoFocus);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/player_controls/res/player_fwd.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbForward->setIcon(icon4);

        lytControls->addWidget(pbForward);

        pbNext = new QPushButton(horizontalLayoutWidget);
        pbNext->setObjectName(QString::fromUtf8("pbNext"));
        pbNext->setEnabled(false);
        pbNext->setFocusPolicy(Qt::NoFocus);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/player_controls/res/player_end.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbNext->setIcon(icon5);

        lytControls->addWidget(pbNext);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        lytControls->addItem(horizontalSpacer);

        pbSetStart = new QPushButton(horizontalLayoutWidget);
        pbSetStart->setObjectName(QString::fromUtf8("pbSetStart"));
        pbSetStart->setEnabled(false);
        sizePolicy.setHeightForWidth(pbSetStart->sizePolicy().hasHeightForWidth());
        pbSetStart->setSizePolicy(sizePolicy);
        pbSetStart->setMaximumSize(QSize(32, 16777215));
        pbSetStart->setFocusPolicy(Qt::NoFocus);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/player_controls/res/set_start.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSetStart->setIcon(icon6);

        lytControls->addWidget(pbSetStart);

        pbSetEnd = new QPushButton(horizontalLayoutWidget);
        pbSetEnd->setObjectName(QString::fromUtf8("pbSetEnd"));
        pbSetEnd->setEnabled(false);
        sizePolicy.setHeightForWidth(pbSetEnd->sizePolicy().hasHeightForWidth());
        pbSetEnd->setSizePolicy(sizePolicy);
        pbSetEnd->setMaximumSize(QSize(32, 16777215));
        pbSetEnd->setFocusPolicy(Qt::NoFocus);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/player_controls/res/set_end.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSetEnd->setIcon(icon7);

        lytControls->addWidget(pbSetEnd);

        pbSave = new QPushButton(horizontalLayoutWidget);
        pbSave->setObjectName(QString::fromUtf8("pbSave"));
        pbSave->setEnabled(false);
        sizePolicy.setHeightForWidth(pbSave->sizePolicy().hasHeightForWidth());
        pbSave->setSizePolicy(sizePolicy);
        pbSave->setMaximumSize(QSize(32, 16777215));
        pbSave->setFocusPolicy(Qt::NoFocus);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/player_controls/res/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSave->setIcon(icon8);

        lytControls->addWidget(pbSave);


        lytLeft->addLayout(lytControls);

        lblStatus = new QLabel(horizontalLayoutWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setMaximumSize(QSize(16777215, 24));

        lytLeft->addWidget(lblStatus);


        lytMain->addLayout(lytLeft);

        lytRight = new QVBoxLayout();
        lytRight->setObjectName(QString::fromUtf8("lytRight"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        lytRight->addWidget(label);

        cbCameras = new QComboBox(horizontalLayoutWidget);
        cbCameras->setObjectName(QString::fromUtf8("cbCameras"));

        lytRight->addWidget(cbCameras);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        lytRight->addWidget(label_2);

        cbDates = new QComboBox(horizontalLayoutWidget);
        cbDates->setObjectName(QString::fromUtf8("cbDates"));

        lytRight->addWidget(cbDates);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        lytRight->addWidget(label_3);

        lstRecords = new QListWidget(horizontalLayoutWidget);
        lstRecords->setObjectName(QString::fromUtf8("lstRecords"));

        lytRight->addWidget(lstRecords);

        pbClose = new QPushButton(horizontalLayoutWidget);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        lytRight->addWidget(pbClose);


        lytMain->addLayout(lytRight);


        retranslateUi(PlayerDialog);
        QObject::connect(pbClose, SIGNAL(clicked()), PlayerDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(PlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *PlayerDialog)
    {
        PlayerDialog->setWindowTitle(QApplication::translate("PlayerDialog", "MJPEG player", 0, QApplication::UnicodeUTF8));
        pbPrev->setText(QString());
        pbBack->setText(QString());
        pbPlay->setText(QString());
        pbForward->setText(QString());
        pbNext->setText(QString());
        pbSetStart->setText(QString());
        pbSetEnd->setText(QString());
        pbSave->setText(QString());
        lblStatus->setText(QApplication::translate("PlayerDialog", "#", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlayerDialog", "Source:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlayerDialog", "Date:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlayerDialog", "Records:", 0, QApplication::UnicodeUTF8));
        pbClose->setText(QApplication::translate("PlayerDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlayerDialog: public Ui_PlayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERDIALOG_H
