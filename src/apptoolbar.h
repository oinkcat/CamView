#ifndef APPTOOLBAR_H
#define APPTOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QSlider>
#include <QIcon>
#include <QPainter>
#include <QFontDatabase>
#include <QBrush>
#include <QLinearGradient>
#include <QDateTime>
#include <QTimer>
#include <QAction>
#include <QEvent>
#include "config.h"

// Main toolbar with clock
class AppToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit AppToolBar(QWidget *parent = 0);
    void toggleAudioButton(bool visible);
    
protected:
    void paintEvent(QPaintEvent *);

private:
    void putButtons();
    QPushButton *pbClose;
    QPushButton *pbMinimize;
    QPushButton *pbPlayer;
    QPushButton *pbSettings;
    QPushButton *pbAudio;
    QSlider *volumeSlider;
    QAction *audioSeparator;
    QTimer updater;
    QString clockFontFamily;
    int prevMinute;

signals:
    void closeClicked();
    void minimizeClicked();
    void playerClicked();
    void settingsClicked();
    void audioClicked(bool checked);
    void volumeChanged(int newValue);
    
private slots:
    void checkTime();

};

#endif // APPTOOLBAR_H
