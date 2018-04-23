#include "linker.h"
#include <QPen>
#include <QDebug>

Linker::Linker(Port *source, Port *dest, qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent) : QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    if ((source->isOut() == dest->isOut()) || source->blockPtr == dest->blockPtr || source->getType() != dest->getType()) {
        throw 1;
    }
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
