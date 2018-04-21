#include "canvas.h"



Canvas::Canvas(MainWindow *parent) : QGraphicsScene(parent)
{
    parentWindow = parent;
}

void Canvas::Additem(qreal x, qreal y)
{
    QPen pen = QPen();
    QBrush brush = QBrush();
    this->addRect(x-260,y-50, 75, 125, pen , brush);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    Additem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y());
}
