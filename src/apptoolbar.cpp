#include "apptoolbar.h"

const int TIME_Y_OFFSET = 200;
const int TIME_UPDATE_INTERVAL = 2000;

const int SLIDER_HEIGHT = 300;
const int SLIDER_MAX = 10;

AppToolBar::AppToolBar(QWidget *parent) :
    QToolBar(parent), prevMinute(-1)
{
    this->setMovable(false);
    this->putButtons();

    connect(&updater, SIGNAL(timeout()), SLOT(checkTime()));
    updater.start(TIME_UPDATE_INTERVAL);

    // Load font for time display
    int fid = QFontDatabase::addApplicationFont(":/new/font/res/trs-million.regular.ttf");
    this->clockFontFamily = QFontDatabase::applicationFontFamilies(fid).at(0);

    this->installEventFilter(this);
}

void AppToolBar::putButtons()
{
    pbClose = new QPushButton(QIcon(":/new/controls/res/close.png"), QString(), this);
    pbClose->setFocusPolicy(Qt::NoFocus);
    pbClose->setToolTip("Close application");
    connect(pbClose, SIGNAL(clicked()), SIGNAL(closeClicked()));
    this->addWidget(pbClose);

    pbMinimize = new QPushButton(QIcon(":/new/controls/res/minimize.png"), QString(), this);
    pbMinimize->setFocusPolicy(Qt::NoFocus);
    pbMinimize->setToolTip("Minimize window");
    connect(pbMinimize, SIGNAL(clicked()), SIGNAL(minimizeClicked()));
    this->addWidget(pbMinimize);

    this->addSeparator();

    pbPlayer = new QPushButton(QIcon(":/new/controls/res/video.png"), QString(), this);
    pbPlayer->setFocusPolicy(Qt::NoFocus);
    pbPlayer->setToolTip("Recorded video player");
    connect(pbPlayer, SIGNAL(clicked()), SIGNAL(playerClicked()));
    this->addWidget(pbPlayer);

    // Only editors can see settings button
    if(Config::getInstance()->getCanEdit()) {
        pbSettings = new QPushButton(QIcon(":/new/controls/res/settings.png"), QString(), this);
        pbSettings->setFocusPolicy(Qt::NoFocus);
        pbSettings->setToolTip("Appliction settings");
        connect(pbSettings, SIGNAL(clicked()), SIGNAL(settingsClicked()));
        this->addWidget(pbSettings);
    }

    audioSeparator = this->addSeparator();

    pbAudio = new QPushButton(QIcon(":/new/controls/res/audio.png"), QString(), this);
    pbAudio->setCheckable(true);
    pbAudio->setFocusPolicy(Qt::NoFocus);
    pbAudio->setToolTip("Audio on/off");
    connect(pbAudio, SIGNAL(clicked(bool)), SIGNAL(audioClicked(bool)));
    this->addWidget(pbAudio);

    volumeSlider = new QSlider(Qt::Vertical, this);
    volumeSlider->setMinimum(-SLIDER_MAX);
    volumeSlider->setMaximum(SLIDER_MAX);
    volumeSlider->setTickPosition(QSlider::TicksRight);
    volumeSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    volumeSlider->setFocusPolicy(Qt::NoFocus);
    volumeSlider->setEnabled(false);
    volumeSlider->resize(this->width(), SLIDER_HEIGHT);
    connect(volumeSlider, SIGNAL(sliderMoved(int)), SIGNAL(volumeChanged(int)));
    this->addWidget(volumeSlider);

    connect(pbAudio, SIGNAL(clicked(bool)), volumeSlider, SLOT(setEnabled(bool)));

    toggleAudioButton(false);
}

// Set visibility of audio button
void AppToolBar::toggleAudioButton(bool visible)
{
    pbAudio->setChecked(false);
    pbAudio->setVisible(visible);
    volumeSlider->setVisible(visible);
    volumeSlider->setValue(0);
    audioSeparator->setVisible(visible);
    this->update();
}

// Toolbar's paint event. Paints gradient background and clock
void AppToolBar::paintEvent(QPaintEvent *)
{
    // FIX?
    pbAudio->setVisible(audioSeparator->isVisible());
    volumeSlider->setVisible(pbAudio->isVisible());

    QPainter painter(this);

    // Background
    QLinearGradient pattern(0, 0, this->width(), 0);
    pattern.setColorAt(0, Qt::darkGray);
    pattern.setColorAt(1, Qt::black);
    QBrush gradient(pattern);
    painter.setBrush(gradient);
    painter.drawRect(this->rect());

    // Clock
    QDateTime now = QDateTime::currentDateTime();
    QString time = now.toString("hh:mm");
    QStringList chars;
    for(QString::const_iterator it = time.begin(); it != time.end(); ++it) {
        chars.append(*it);
    }
    int yPos = this->height() - TIME_Y_OFFSET;
    QRect timeRect(0, yPos, this->width(), yPos);
    painter.setPen(Qt::black);
    painter.drawLine(0, yPos - 5, this->width(), yPos - 5);
    painter.setPen(Qt::lightGray);
    painter.setFont(QFont(this->clockFontFamily, 24));
    painter.drawText(timeRect, Qt::TextWrapAnywhere | Qt::AlignHCenter, chars.join("\n"));
}

// Check current time and post panel update message if changed
void AppToolBar::checkTime()
{
    int nowMinute = QDateTime::currentDateTime().time().minute();
    if(nowMinute != prevMinute) {
        this->update();
        prevMinute = nowMinute;
    }
}
