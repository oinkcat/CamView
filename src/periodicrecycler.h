#ifndef PERIODICRECYCLER_H
#define PERIODICRECYCLER_H

#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include "config.h"

// Removes old camera records
class PeriodicRecycler : public QThread
{
    Q_OBJECT

private:
    static PeriodicRecycler *instance;
    explicit PeriodicRecycler(QObject * = 0);
    bool removeDir(const QString &dirName);
    QTimer checker;
    bool enabled;
    QDate lastRecycleDate;

private slots:
    void checkTime();

public:
    static PeriodicRecycler *getInstance();
    virtual void run();

signals:
    void timeToRecycle();
    
public slots:
    void setEnabled(bool enabled);
    void performRecycle();
    
};

#endif // PERIODICRECYCLER_H
