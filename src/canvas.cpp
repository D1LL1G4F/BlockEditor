#include "canvas.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QInputDialog>
#include <cmath>
#include "mainwindow.h"
#include "linker.h"
#include <QMessageBox>
#include <string>

#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 125


Canvas::Canvas(MainWindow *parent) : QGraphicsScene(parent)
{
    parentWindow = parent;
    lineSourceValid = false;
    movingBlock = nullptr;
}

void Canvas::clearAll()
{
    clear();
    scheme.clear();
    blockItems.clear();
}

Scheme *Canvas::getScheme()
{
    return &scheme;
}

void Canvas::Additem(qreal x, qreal y)
{
    if (parentWindow->getSelectedItem() < MainWindow::ITEM_LINKER) {
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
                QPen pen = QPen();
                pen.setWidth(6);
                pen.setColor(QColor(0,0,255,255));
                tmpLine = addLine(getPortPtrFromItem(item)->getX()+8,getPortPtrFromItem(item)->getY()+8,mouseEvent->scenePos().x(),mouseEvent->scenePos().y(),pen);

            } else {
                lineSourceValid = false;
                return;
            }
        }
        if (item->data(1) == "Block" && parentWindow->getSelectedItem() == MainWindow::ITEM_MOVER) {
            movingBlock = scheme.getBlock(item->data(0).toInt());
            movingBlock->setCoords(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
            reloadScheme();
            return;
        }
        if (item->data(1) == "Block" && parentWindow->getSelectedItem() == MainWindow::ITEM_DESTRUCTOR) {
            scheme.removeBLock(item->data(0).toInt());
            reloadScheme();
            return;
        }
        if (item->data(0) == "Linker" && parentWindow->getSelectedItem() == MainWindow::ITEM_DESTRUCTOR) {
            scheme.removeLinkOnPort(item->data(1).toDouble(),item->data(2).toDouble());
            reloadScheme();
            parentWindow->getOutputScr()->setText("");
            return;
        }
        Additem(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }
    if (movingBlock && parentWindow->getSelectedItem() == MainWindow::ITEM_MOVER) {
        movingBlock->setCoords(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
        reloadScheme();
        movingBlock = nullptr;
        return;
    }
    if (parentWindow->getSelectedItem() == MainWindow::ITEM_LINKER) {
        if (!lineSourceValid) {
            return;
        }
        delete tmpLine;
        lineSourceValid = false;
        double targetX;
        double targetY;
        QGraphicsItem *item = this->itemAt(mouseEvent->scenePos().x(),mouseEvent->scenePos().y(),QTransform());
        Block *blockPtr;
        Port *destPort;
        if (item->data(0) == "INPUT" || item->data(0) == "OUTPUT") {
            int portIdx = item->data(1).toInt();
            int blckIdx = item->data(2).toInt();
            blockPtr = scheme.getBlock(blckIdx);
            if (item->data(0) == "INPUT") {
                destPort = blockPtr->getInPort(portIdx);
                targetX = blockPtr->getInPort(portIdx)->getX();
                targetY = blockPtr->getInPort(portIdx)->getY();
            } else {
                destPort = blockPtr->getOutPort(portIdx);
                targetX = blockPtr->getOutPort(portIdx)->getX();
                targetY = blockPtr->getOutPort(portIdx)->getY();
            }
        } else {
            return;
        }
        Port *sourcePort = getPortPtrFromItem(sourceItem);
        double sourceX = sourcePort->getX();
        double sourceY = sourcePort->getY();
        Linker *line;
        bool err = false;
        try {
            line = new Linker(parentWindow->getOutputScr(), sourcePort,destPort,sourceX+8,sourceY+8, targetX+8, targetY+8);
            line->setZValue(1);
            line->setData(0,"Linker");
            line->setData(1,sourceX);
            line->setData(2,sourceY);
            line->setData(3,targetX);
            line->setData(4,targetY);
        }
        catch (char const *error){
            std::string msg("Incompatible port types ");
            msg += string(error);
            err = true;
            QMessageBox::warning(NULL, tr("BlockEditor WARNING"), tr(msg.c_str()), QMessageBox::Cancel);
        }
        if (!err) {
            addItem(line);
            changeCircleColor(sourceItem,QColor(0,0,255,255));
            changeCircleColor(item,QColor(0,0,255,255));
        }
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (parentWindow->getSelectedItem() == MainWindow::ITEM_LINKER && lineSourceValid) {
        delete tmpLine;
        QPen pen = QPen();
        pen.setWidth(6);
        pen.setColor(QColor(0,0,255,255));
        tmpLine = addLine(getPortPtrFromItem(sourceItem)->getX()+8,getPortPtrFromItem(sourceItem)->getY()+8,mouseEvent->scenePos().x(),mouseEvent->scenePos().y(),pen);
    } else if (parentWindow->getSelectedItem() == MainWindow::ITEM_MOVER && movingBlock) {
        movingBlock->setCoords(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
        reloadScheme();
    } else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void Canvas::createBlock(double x, double y)
{
    for (int i = 0; i < scheme.getLastBlockIndex()+1 ; i++) { // check overlaping
        Block *blockPtr = scheme.getBlock(i);
        if (fabs(blockPtr->getX() - x) < 75 &&  fabs(blockPtr->getY() - y) < 125)
            return;
    }
    QPen pen = QPen();
    pen.setWidth(4);
    QBrush brush = QBrush();
    double rHeight = BLOCK_HEIGHT;
    double rWidth = BLOCK_WIDTH;
    QGraphicsItem *blockItem;
    blockItem = this->addRect(x,y, rWidth, rHeight, pen , brush);
    QGraphicsTextItem * txt = new QGraphicsTextItem;
    txt->setPos(x+20,y+3);
    txt->setPlainText(getActualBlockName(parentWindow->getSelectedItem()));

    this->addItem(txt);
    Block *b = scheme.addBlock(new Block(parentWindow->getSelectedItem(), x, y, rWidth, rHeight));
    blockItem->setData(0,QVariant(scheme.getLastBlockIndex()));
    blockItem->setData(1,QVariant("Block"));
    blockItems.push_back(blockItem);
    pen.setColor(QColor(255,0,0,255));
    for (int i=0; i < b->inPortsNumber; i++) { // draw in ports
        QGraphicsEllipseItem *circle = this->addEllipse(b->getInPort(i)->getX(),b->getInPort(i)->getY(),17,17,pen,brush);
        circle->setData(0,QVariant("INPUT"));
        circle->setData(1,QVariant(i));
        circle->setData(2,QVariant(scheme.getLastBlockIndex()));
        circle->setZValue(100);
        QGraphicsTextItem * portTxt = new QGraphicsTextItem;
        portTxt->setPos(b->getInPort(i)->getX()+5,b->getInPort(i)->getY()+12);
        portTxt->setPlainText(QString("in") + QString::number(i,10));
        this->addItem(portTxt);
    }
    pen.setColor(QColor(0,0,0,255));
    for (int i=0; i < b->outPortsNumber; i++) { // draw out ports
        QGraphicsEllipseItem *circle = this->addEllipse(b->getOutPort(i)->getX(),b->getOutPort(i)->getY(),17,17,pen,brush);
        circle->setData(0,QVariant("OUTPUT"));
        circle->setData(1,QVariant(i));
        circle->setData(2,QVariant(scheme.getLastBlockIndex()));
        circle->setZValue(100);
        QGraphicsTextItem * portTxt = new QGraphicsTextItem;
        portTxt->setPos(b->getOutPort(i)->getX()-15,b->getOutPort(i)->getY()+12);
        portTxt->setPlainText(QString("out") + QString::number(i,10));
        this->addItem(portTxt);
    }
}

QString Canvas::getActualBlockName(int type)
{
    switch (type) {
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

void Canvas::reloadScheme()
{
    scheme.resetSimulation();
    clear();
    blockItems.clear();
    for (int blockIdx = 0; blockIdx < scheme.getLastBlockIndex()+1 ; blockIdx++) {
        Block *blck;
        blck = scheme.getBlock(blockIdx);
        QPen pen = QPen();
        pen.setWidth(4);
        QBrush brush = QBrush();
        double rHeight = 125;
        double rWidth = 75;
        QGraphicsItem *blockItem;
        blockItem = this->addRect(blck->getX(), blck->getY() ,rWidth ,rHeight, pen , brush);
        QGraphicsTextItem * txt = new QGraphicsTextItem;
        txt->setPos(blck->getX()+20,blck->getY()+3);
        txt->setPlainText(getActualBlockName(blck->getType()));
        this->addItem(txt);
        blockItem->setData(0,QVariant(blockIdx));
        blockItem->setData(1,QVariant("Block"));
        blockItems.push_back(blockItem);
        pen.setColor(QColor(255,0,0,255));
        for (int i=0; i < blck->inPortsNumber; i++) { // draw in ports
            QGraphicsEllipseItem *circle = this->addEllipse(blck->getInPort(i)->getX(),blck->getInPort(i)->getY(),17,17,pen,brush);
            circle->setData(0,QVariant("INPUT"));
            circle->setData(1,QVariant(i));
            circle->setData(2,QVariant(blockIdx));
            circle->setZValue(100);
            QGraphicsTextItem * portTxt = new QGraphicsTextItem;
            portTxt->setPos(blck->getInPort(i)->getX()+5,blck->getInPort(i)->getY()+12);
            portTxt->setPlainText(QString("in") + QString::number(i,10));
            this->addItem(portTxt);
        }
        pen.setColor(QColor(0,0,0,255));
        for (int i=0; i < blck->outPortsNumber; i++) { // draw out ports
            QGraphicsEllipseItem *circle = this->addEllipse(blck->getOutPort(i)->getX(),blck->getOutPort(i)->getY(),17,17,pen,brush);
            circle->setData(0,QVariant("OUTPUT"));
            circle->setData(1,QVariant(i));
            circle->setData(2,QVariant(blockIdx));
            circle->setZValue(100);
            QGraphicsTextItem * portTxt = new QGraphicsTextItem;
            portTxt->setPos(blck->getOutPort(i)->getX()-15,blck->getOutPort(i)->getY()+12);
            portTxt->setPlainText(QString("out") + QString::number(i,10));
            this->addItem(portTxt);
        }
    }
    for (int blockIdx = 0; blockIdx < scheme.getLastBlockIndex()+1 ; blockIdx++) {
        Block *blck;
        blck = scheme.getBlock(blockIdx);
        for (int i=0; i < blck->outPortsNumber; i++) { // add linkers
            Port *outPort;
            outPort = blck->getOutPort(i);
            if (outPort->pairedPort) {
                Linker *line;
                bool err = false;
                try {
                    line = new Linker(parentWindow->getOutputScr(), outPort,outPort->pairedPort,outPort->getX()+8,outPort->getY()+8, outPort->pairedPort->getX()+8, outPort->pairedPort->getY()+8);
                    line->setZValue(1);
                    line->setData(0,"Linker");
                    line->setData(1,outPort->getX());
                    line->setData(2,outPort->getY());
                    line->setData(3,outPort->pairedPort->getX());
                    line->setData(4,outPort->pairedPort->getY());
                }
                catch (char const *error){
                    std::string msg("Incompatible port types ");
                    msg += string(error);
                    err = true;
                    QMessageBox::warning(NULL, tr("BlockEditor WARNING"), tr(msg.c_str()), QMessageBox::Cancel);
                }
                if (!err) {
                    addItem(line);
                    QGraphicsItem *firstCircle = this->itemAt(outPort->getX()+2,outPort->getY()+2,QTransform());
                    changeCircleColor(firstCircle,QColor(0,0,255,255));
                    QGraphicsItem *secondCircle = this->itemAt(outPort->pairedPort->getX()+2,outPort->pairedPort->getY()+2,QTransform());
                    changeCircleColor(secondCircle,QColor(0,0,255,255));
                }
            }
        }
        for (int i=0; i < blck->inPortsNumber; i++) { // configure set ports
            Port *p;
            p = blck->getInPort(i);
            if (p->isSet()) {
                changeCircleColor(this->itemAt(p->getX()+2,p->getY()+2,QTransform()),QColor(0,255,0,255));
            }
        }
    }
}

void Canvas::changeRectColor(int idx, QColor color)
{
    QGraphicsItem *blckItem = blockItems[idx];
    Block *block = scheme.getBlock(idx);
    delete blckItem;
    QPen pen = QPen();
    pen.setWidth(4);
    pen.setColor(color);
    QBrush brush = QBrush();
    double rHeight = 125;
    double rWidth = 75;
    blckItem = this->addRect(block->getX(),block->getY(), rWidth, rHeight, pen , brush);
    blckItem->setZValue(-1);
    blockItems.at(idx) = blckItem;
}

void Canvas::setScheme(boost::property_tree::ptree root)
{
    scheme.loadScheme(root);
    reloadScheme();
}
