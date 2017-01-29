#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <QDir>
#include <QIcon>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include "config.h"
#include "converter.h"
#include "playerwidget.h"

namespace Ui {
class PlayerDialog;
}

// Recordings player window
class PlayerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlayerDialog(QWidget *parent = 0);
    ~PlayerDialog();

protected:
    bool eventFilter(QObject * object, QEvent * event);
    
private:
    void finishUI();
    void controlUIAfterRecordSelection();
    void controlUIAfterSeek();
    void populateCameras();
    void clearSelection();
    QPair<int, int> clipRanges;
    QString getSelectedRecordPath();
    PlayerWidget *player;
    Ui::PlayerDialog *ui;
    QIcon *icPlay;
    QIcon *icPause;

private slots:
    void conversionProgress();
    void recordConverted();

public slots:
    void controlPlaying(bool playing);
    void populateRecordDates(QString camName);
    void populateRecords(QString date);
    void loadRecord(QString time);
    void seekByTime(int mtime);
    void doSingleStep();
    void moveToAnotherRecord();
    void setClipRange();
    void saveClip();
};

#endif // PLAYERDIALOG_H
