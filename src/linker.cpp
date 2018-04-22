#include "linker.h"
#include <QPen>

Linker::Linker(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent) : QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(QColor(0,0,255,255));
    setPen(pen);
    setAcceptHoverEvents(true);
}

void Linker::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(QColor(0,0,0,255));
    setPen(pen);
}

void Linker::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(QColor(0,0,255,255));
    setPen(pen);
}
