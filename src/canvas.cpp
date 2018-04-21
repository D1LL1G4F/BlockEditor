#include "canvas.h"


Canvas::Canvas(MainWindow *parent) : QGraphicsScene(parent)
{
    parentWindow = parent;
}

void Canvas::Additem(qreal x, qreal y)
{
    QPen pen = QPen();
    QBrush brush = QBrush();
    this->addRect(x,y, 75, 125, pen , brush);
    Block &b = scheme.addBlock(Block(parentWindow->getSelectedItem(), x, y));

}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    Additem(mouseEvent->screenPos().x() - offsetX, mouseEvent->screenPos().y() - offsetY);
}
