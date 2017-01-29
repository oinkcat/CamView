#include "playerdialog.h"
#include "ui_playerdialog.h"

const int TIME_LENGTH = 8;
const int SLIDER_STEP = 100;

PlayerDialog::PlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint);
    this->setFixedSize(this->size());
    this->clipRanges = qMakePair(-1, -1);
    populateCameras();

    // Icons for play/pause button
    icPlay = new QIcon(":/new/player_controls/res/player_play.png");
    icPause= new QIcon(":/new/player_controls/res/player_pause.png");

    finishUI();
    ui->sldPosition->installEventFilter(this);
}

void PlayerDialog::finishUI()
{
    player = new PlayerWidget(ui->frmImage);
    player->setParent(ui->frmImage);
    ui->sldPosition->setSingleStep(SLIDER_STEP);
    ui->sldPosition->setPageStep(SLIDER_STEP);
    ui->lblStatus->setText("");
    ui->pbSetStart->setVisible(false);
    ui->pbSetEnd->setVisible(false);

    connect(ui->cbCameras, SIGNAL(currentIndexChanged(QString)), SLOT(populateRecordDates(QString)));
    connect(ui->cbDates, SIGNAL(currentIndexChanged(QString)), SLOT(populateRecords(QString)));
    connect(ui->lstRecords, SIGNAL(currentTextChanged(QString)), SLOT(loadRecord(QString)));
    connect(ui->sldPosition, SIGNAL(sliderMoved(int)), SLOT(seekByTime(int)));
    connect(ui->sldPosition, SIGNAL(valueChanged(int)), SLOT(seekByTime(int)));
    connect(ui->pbBack, SIGNAL(clicked()), SLOT(doSingleStep()));
    connect(ui->pbForward, SIGNAL(clicked()), SLOT(doSingleStep()));
    connect(ui->pbPrev, SIGNAL(clicked()), SLOT(moveToAnotherRecord()));
    connect(ui->pbNext, SIGNAL(clicked()), SLOT(moveToAnotherRecord()));
    connect(ui->pbPlay, SIGNAL(clicked()), player, SLOT(play()));
    connect(ui->pbSetStart, SIGNAL(clicked()), SLOT(setClipRange()));
    connect(ui->pbSetEnd, SIGNAL(clicked()), SLOT(setClipRange()));
    connect(ui->pbSave, SIGNAL(clicked()), SLOT(saveClip()));
    connect(player, SIGNAL(positionChanged(int)), ui->sldPosition, SLOT(setValue(int)));
    connect(player, SIGNAL(playingStateChanged(bool)), SLOT(controlPlaying(bool)));
}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::populateCameras()
{
    QDir dumpDir(Config::getInstance()->getDumpDir());
    QStringList cams(dumpDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name));
    ui->cbCameras->addItem("");
    ui->cbCameras->addItems(cams);
}

void PlayerDialog::populateRecordDates(QString camName)
{
    ui->cbDates->clear();
    ui->lstRecords->clear();

    if(camName.length() > 0) {
        QDir camDir(Config::getInstance()->getDumpDir().append('/').append(camName));
        QStringList dates(camDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Time));
        foreach(QString dateDir, dates) {
            ui->cbDates->addItem(dateDir.replace('_', '.'));
        }
        populateRecords(ui->cbDates->currentText());
    }
}

void PlayerDialog::populateRecords(QString date)
{
    ui->lstRecords->clear();

    if(date.length() > 0) {
        QDir recDir(QString("%1/%2/%3").arg(Config::getInstance()->getDumpDir(),
                                            ui->cbCameras->currentText(),
                                            ui->cbDates->currentText().replace('.', '_')));
        QStringList exts("*.mjpeg");
        QStringList records(recDir.entryList(exts, QDir::Files, QDir::Name));
        foreach(QString recName, records) {
            ui->lstRecords->addItem(recName.replace('_', ':').left(TIME_LENGTH));
        }
    }
}

QString PlayerDialog::getSelectedRecordPath()
{
    QStringList pathParts(Config::getInstance()->getDumpDir());
    pathParts << ui->cbCameras->currentText();
    pathParts << ui->cbDates->currentText().replace('.', '_');
    pathParts << ui->lstRecords->currentItem()->text().replace(':', '_').append(".mjpeg");

    return QString(pathParts.join("/"));
}

void PlayerDialog::loadRecord(QString time)
{
    if(time.length() > 0) {
        player->loadFile(getSelectedRecordPath());

        controlUIAfterRecordSelection();
    }
}

void PlayerDialog::controlUIAfterRecordSelection()
{
    ui->pbPlay->setEnabled(true);
    int selRecordIndex = ui->lstRecords->currentRow();
    ui->pbPrev->setEnabled(selRecordIndex > 0);
    ui->pbNext->setEnabled(selRecordIndex < ui->lstRecords->count() - 1);
    ui->pbSave->setEnabled(true);

    ui->sldPosition->setValue(0);
    ui->sldPosition->setEnabled(true);
    int videoLength = player->getLength();
    ui->sldPosition->setMaximum(videoLength);

    clearSelection();
    controlUIAfterSeek();
}

void PlayerDialog::controlUIAfterSeek()
{
    ui->pbBack->setEnabled(ui->sldPosition->value() > 0);
    ui->pbForward->setEnabled(ui->sldPosition->value() < ui->sldPosition->maximum() - 1);
}

void PlayerDialog::controlPlaying(bool playing)
{
    ui->pbPlay->setIcon(playing ? *icPause : *icPlay);
}

void PlayerDialog::seekByTime(int mtime)
{
    if(!player->isPlaying()) {
        player->seek(mtime);
    }

    controlUIAfterSeek();
}

void PlayerDialog::doSingleStep()
{
    QPushButton *pbSender = qobject_cast<QPushButton*>(sender());
    if(pbSender != NULL) {
        int delta = pbSender == ui->pbBack ? -1 : 1;
        player->singleStep(delta);
    }
}

void PlayerDialog::moveToAnotherRecord()
{
    QPushButton *pbSender = qobject_cast<QPushButton*>(sender());
    if(pbSender != NULL) {
        int recIndex = ui->lstRecords->currentRow();
        int newIndex = pbSender == ui->pbPrev ? recIndex - 1 : recIndex + 1;
        ui->lstRecords->setCurrentRow(newIndex);
    }
}

/* REGION: Range selection and clip saving */
void PlayerDialog::setClipRange()
{
    bool isStart = sender() == ui->pbSetStart;
    if(isStart) {
        clipRanges.first = ui->sldPosition->value();
        // Check right bound
        if(clipRanges.second == -1)
            clipRanges.second = player->getLength();
        else if(clipRanges.second < clipRanges.first)
            clipRanges.second = clipRanges.first;
    } else {
        clipRanges.second = ui->sldPosition->value();
        // Check Left bound
        if(clipRanges.first == -1)
                    clipRanges.first = 0;
        else if(clipRanges.first > clipRanges.second)
            clipRanges.first = clipRanges.second;
    }

    ui->sldPosition->update();
}

bool PlayerDialog::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->sldPosition && event->type() == QEvent::Paint) {
        // Draw record clipping region
        QSlider *sldPos = qobject_cast<QSlider*>(object);
        int maxVal = sldPos->maximum();

        if(maxVal > 0) {
            QPainter painter(sldPos);
            int maxWidth = ui->sldPosition->width() - 1;
            int height = ui->sldPosition->height();

            int xs = clipRanges.first * maxWidth / maxVal;
            int xe = clipRanges.second * maxWidth / maxVal;

            bool rangeValid = clipRanges.first != -1 && clipRanges.second != -1;
            if(rangeValid) {
                QColor rangeColor(200, 200, 255);
                painter.fillRect(xs, 0, xe - xs, height, rangeColor);
            }

            if(clipRanges.first != -1)
                painter.drawLine(xs, 0, xs, height);
            if(clipRanges.second != -1)
                painter.drawLine(xe, 0, xe, height);
        }
    }
    return false;
}

void PlayerDialog::clearSelection()
{
    clipRanges.first = clipRanges.second = -1;
    ui->pbSetStart->setEnabled(true);
    ui->pbSetEnd->setEnabled(true);
    ui->sldPosition->update();
}

void PlayerDialog::conversionProgress()
{
    static int n = 0;
    QString dots(n++ % 10, '.');
    QString status(QString("Converting and saving").append(dots));
    ui->lblStatus->setText(status);
}

void PlayerDialog::recordConverted()
{
    ui->lblStatus->setText("");
    QApplication::restoreOverrideCursor();
    QMessageBox::information(this, QString("Converted"),
                             QString("Record successfully converted!"));
}

void PlayerDialog::saveClip()
{
    if(Converter::canConvert()) {
        // Ask user for exported file name
        QString trgFileName = QFileDialog::getSaveFileName(
                    this, QString("Choose exported file name"),
                    QString(), QString("MP4 video (*.mp4)"));

        if(trgFileName.trimmed().length() > 0) {
            QApplication::setOverrideCursor(Qt::WaitCursor);

            // Check the extension
            if(!trgFileName.endsWith(".mp4"))
                trgFileName = trgFileName.append(".mp4");

            // Save record with clipping and conversion
            Converter *conv = new Converter(getSelectedRecordPath(), trgFileName);
            if(clipRanges.first > -1 && clipRanges.second > -1) {
                conv->setClipBounds(clipRanges.first, clipRanges.second);
            }
            connect(conv, SIGNAL(progressChanged()), SLOT(conversionProgress()));
            connect(conv, SIGNAL(finished()), SLOT(recordConverted()));
            conv->start();
        }
    } else {
        QMessageBox::critical(this, QString("Error occured"),
                              QString("mencoder is not installed!"));
    }
}
/* ENDREGION */
