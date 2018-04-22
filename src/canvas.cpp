#include "canvas.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QInputDialog>
#include "mainwindow.h"


Canvas::Canvas(MainWindow *parent) : QGraphicsScene(parent)
{
    parentWindow = parent;
    lineSourceValid = false;
}

void Canvas::Additem(qreal x, qreal y)
{
    if (parentWindow->getSelectedItem() != MainWindow::ITEM_LINKER) {
        createBlock(x,y);
    }

}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        QGraphicsItem *item = this->itemAt(mouseEvent->scenePos().x(),mouseEvent->scenePos().y(),QTransform());
        if (item->data(0) == "INPUT") {
            bool ok;
            Port *port = getPortPtrFromItem(item);
            int minVal;
            int maxVal;
            QString label;
            if (port->getType() == "logical") {
                minVal = 0;
                maxVal = 1;
                label = "logical port value (0/1):";
            } else {
                minVal = -2147483647;
                maxVal = 2147483647;
                label = "decimal port value (-2147483647 - 21474836470:)";
            }
            double portVal = (double)QInputDialog::getInt(NULL,QString("Enter port value"), label, 0, minVal, maxVal, 1, &ok, Qt::WindowFlags());
            if (ok) {
                changeCircleColor(item,QColor(0,255,0,255));
                port->set(portVal);
            }
        }
        return;
    } else {
        QGraphicsItem *item = this->itemAt(mouseEvent->scenePos().x(),mouseEvent->scenePos().y(),QTransform());
        if (parentWindow->getSelectedItem() == MainWindow::ITEM_LINKER) {
            if (item->data(0) == "INPUT" || item->data(0) == "OUTPUT") {
                lineSourceValid = true;
                sourceItem = item;

            } else {
                lineSourceValid = false;
                return;
            }
        }
    Additem(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }
    if (parentWindow->getSelectedItem() == MainWindow::ITEM_LINKER) {
        if (!lineSourceValid) {
            return;
        }
        lineSourceValid = false;
        double targetX;
        double targetY;
        QPen pen = QPen();
        pen.setWidth(6);
        pen.setColor(QColor(0,0,255,255));
        QGraphicsItem *item = this->itemAt(mouseEvent->scenePos().x(),mouseEvent->scenePos().y(),QTransform());
        if (item->data(0) == "INPUT" || item->data(0) == "OUTPUT") {
            int portIdx = item->data(1).toInt();
            int blckIdx = item->data(2).toInt();
            Block *blockPtr = scheme.getBlock(blckIdx);
            if (item->data(0) == "INPUT") {
                targetX = blockPtr->getInPort(portIdx)->getX();
                targetY = blockPtr->getInPort(portIdx)->getY();
            } else {
                targetX = blockPtr->getOutPort(portIdx)->getX();
                targetY = blockPtr->getOutPort(portIdx)->getY();
            }
        } else {
            return;
        }
        Port *sourcePort = getPortPtrFromItem(sourceItem);
        double sourceX = sourcePort->getX();
        double sourceY = sourcePort->getY();
        this->addLine(sourceX+8,sourceY+8, targetX+8, targetY+8,pen);
        changeCircleColor(sourceItem,QColor(0,0,255,255));
        changeCircleColor(item,QColor(0,0,255,255));
    }
}

void Canvas::createBlock(double x, double y)
{
    for (int i = 0; i < scheme.getLastBlockIndex()+1 ; i++) { // check overlaping
        Block *blockPtr = scheme.getBlock(i);
        if (abs(blockPtr->getX() - x) < 75 &&  abs(blockPtr->getY() - y) < 125)
            return;
    }
    QPen pen = QPen();
    pen.setWidth(4);
    QBrush brush = QBrush();
    double rHeight = 125;
    double rWidth = 75;
    this->addRect(x,y, rWidth, rHeight, pen , brush);
    QGraphicsTextItem * txt = new QGraphicsTextItem;
    txt->setPos(x+20,y+3);
    txt->setPlainText(getActualBlockName());

    this->addItem(txt);
    Block &b = scheme.addBlock(Block(parentWindow->getSelectedItem(), x, y, rWidth, rHeight));
    pen.setColor(QColor(255,0,0,255));
    for (int i=0; i < b.inPortsNumber; i++) { // draw in ports
        QGraphicsEllipseItem *circle = this->addEllipse(b.getInPort(i)->getX(),b.getInPort(i)->getY(),17,17,pen,brush);
        circle->setData(0,QVariant("INPUT"));
        circle->setData(1,QVariant(i));
        circle->setData(2,QVariant(scheme.getLastBlockIndex()));
    }
    pen.setColor(QColor(0,0,0,255));
    for (int i=0; i < b.outPortsNumber; i++) { // draw out ports
        QGraphicsEllipseItem *circle = this->addEllipse(b.getOutPort(i)->getX(),b.getOutPort(i)->getY(),17,17,pen,brush);
        circle->setData(0,QVariant("OUTPUT"));
        circle->setData(1,QVariant(i));
        circle->setData(2,QVariant(scheme.getLastBlockIndex()));
    }
}

QString Canvas::getActualBlockName()
{
    switch (parentWindow->getSelectedItem()) {
    case MainWindow::ITEM_AND:
        return "AND";
    case MainWindow::ITEM_NAND:
        return "NAND";
    case MainWindow::ITEM_OR:
        return "OR";
    case MainWindow::ITEM_XOR:
        return "XOR";
    case MainWindow::ITEM_ADD:
        return "ADD";
    case MainWindow::ITEM_SUB:
        return "SUB";
    case MainWindow::ITEM_LT:
        return "<";
    case MainWindow::ITEM_GT:
        return ">";
    default:
        return "UNKNOWN BLOCK";
    }
}

void Canvas::changeCircleColor(QGraphicsItem *item, QColor color)
{
    bool input = false;
    if (item->data(0) == "INPUT") {
        input = true;
    }
    int portIdx = item->data(1).toInt();
    int blckIdx = item->data(2).toInt();
    Block *blockPtr = scheme.getBlock(blckIdx);
    delete item;

    QBrush brush = QBrush();
    QPen pen = QPen();
    pen.setWidth(6);
    pen.setColor(color);

    if (input) {
        this->addEllipse(blockPtr->getInPort(portIdx)->getX(),blockPtr->getInPort(portIdx)->getY(),17,17,pen,brush);
    } else {
        this->addEllipse(blockPtr->getOutPort(portIdx)->getX(),blockPtr->getOutPort(portIdx)->getY(),17,17,pen,brush);
    }

}

Port *Canvas::getPortPtrFromItem(QGraphicsItem *item)
{
    int portIdx = item->data(1).toInt();
    int blckIdx = item->data(2).toInt();
    Block *blockPtr = scheme.getBlock(blckIdx);
    if (item->data(0) == "INPUT") {
        return blockPtr->getInPort(portIdx);
    } else {
        return blockPtr->getOutPort(portIdx);
    }
}
