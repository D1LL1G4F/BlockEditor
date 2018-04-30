/*! \file      linker.cpp
 *  \brief     definitoins of Linker class
 *  \author    Matej Knazik
 *  \date      2018
 */

#include "linker.h"
#include <QPen>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QGraphicsSceneHoverEvent>

Linker::Linker(QLabel *output, Port *source, Port *dest, qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent) : QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    if (source->isOut() == dest->isOut()) {
       throw "(cannot connect two output ports or two input ports)";
    }
    if (source->blockPtr == dest->blockPtr) {
        throw "(cannot connect two ports of the same block)";
    }
    if (source->getType() != dest->getType()) {
        throw "(cannot connect binary port with decimal)";
    }
    if (source->isOut()) {
        srcPort = source;
        destPort = dest;
    } else {
        srcPort = dest;
        destPort = source;
    }
    outputScr = output;
    source->pairedPort = dest;
    dest->pairedPort = source;
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(QColor(0,0,255,255));
    setPen(pen);
    setAcceptHoverEvents(true);
    dialogTxt = nullptr;
}

void Linker::hoverEnterEvent(QGraphicsSceneHoverEvent *evnt)
{
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(QColor(0,0,0,255));
    setPen(pen);
    prevOutput = outputScr->text();
    if (srcPort->isSet()) {
        outputScr->setText(QString("Current value: \n") + QString::number(srcPort->getValue()));
    } else {
        outputScr->setText(QString("Current value: \nundefined"));
    }
}

void Linker::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(QColor(0,0,255,255));
    setPen(pen);
    outputScr->setText(prevOutput);
}
