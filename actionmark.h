#ifndef ACTIONMARK_H
#define ACTIONMARK_H

#include <QWidget>
#include <QPainter>

// Current action performing for camera widget
class ActionMark : public QWidget
{
    Q_OBJECT
public:
    enum Action { Move, ExcludeArea };

    explicit ActionMark(QWidget *parent = 0);
    void setEnds(const QPoint &p1, const QPoint &p2);
    void showForAction(Action action);

protected:
    void paintEvent(QPaintEvent *);
    void hideEvent(QHideEvent *);
    
private:
    QPoint startPoint;
    QPoint endPoint;
    Action currentAction;

};

#endif // ACTIONMARK_H
