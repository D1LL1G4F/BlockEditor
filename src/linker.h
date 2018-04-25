#ifndef LINKER_H
#define LINKER_H

#include "port.h"
#include <QGraphicsLineItem>
#include <QLabel>
#include <QString>

class Linker : public QGraphicsLineItem
{
public:
    Linker(QLabel *output,Port *source, Port *dest, qreal x1, qreal y1, qreal x2, qreal y2 ,QGraphicsItem *parent = Q_NULLPTR);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) Q_DECL_OVERRIDE;

private:
    Port *srcPort;
    Port *destPort;
    QGraphicsTextItem *dialogTxt;
    QLabel *outputScr;
    QString prevOutput;
};

#endif // LINKER_H
