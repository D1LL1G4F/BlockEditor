#ifndef LINKER_H
#define LINKER_H

#include <QGraphicsLineItem>


class Linker : public QGraphicsLineItem
{
public:
    Linker(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = Q_NULLPTR);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) Q_DECL_OVERRIDE;

};

#endif // LINKER_H
