#include <QtGui/QApplication>
#include <QMessageBox>
#include <QLocalServer>
#include <QLocalSocket>
#include "mainwindow.h"
#include "config.h"
#include <playerdialog.h>

const int E_OK = 0;
const int E_NOT_SINGLE_INSTANCE = 10;
const int E_NO_CONFIG = 100;

// Uncomment this for player's debug purposes
// #define RUN_PLAYER

int main(int argc, char *argv[])
{
    int exitCode = E_OK;
    QApplication a(argc, argv);

    if(Config::getInstance()->tryFindConfig()) {
        Config::getInstance()->loadConfig();
#ifdef RUN_PLAYER
        PlayerDialog w;
        w.show();
#else
        MainWindow w;
        w.showFullScreen();
#endif
        exitCode = a.exec();
    } else {
        QMessageBox::critical(NULL, "MJPEG camera viewer", "Config file not found!", "OK");
        exitCode = E_NO_CONFIG;
    }

    return exitCode;
}
