#include "actionmark.h"

ActionMark::ActionMark(QWidget *parent) :
    QWidget(parent), currentAction(Move)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->resize(1, 1);
}

void ActionMark::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(currentAction == Move) {
        QPen arrowPen(QBrush(Qt::darkGreen), 3);
        painter.setPen(arrowPen);
        painter.drawLine(startPoint, endPoint);
    } else {
        painter.setPen(Qt::red);
        QRect bounds = this->rect();
        bounds.adjust(0, 0, -1, -1);
        painter.drawRect(bounds);
        painter.drawLine(startPoint, endPoint);
        painter.drawLine(startPoint.x(), endPoint.y(),
                         endPoint.x(), startPoint.y());
    }
}

void ActionMark::hideEvent(QHideEvent *)
{
    this->resize(1, 1);
}

void ActionMark::setEnds(const QPoint &p1, const QPoint &p2)
{
    startPoint = QPoint(p2.x() > p1.x() ? 0 : this->width(),
                        p2.y() > p1.y() ? 0 : this->height());
    endPoint = QPoint(p2.x() < p1.x() ? 0 : this->width(),
                      p2.y() < p1.y() ? 0 : this->height());
}

void ActionMark::showForAction(Action action)
{
    this->currentAction = action;
    this->show();
}
