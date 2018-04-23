#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include "mainwindow.h"
#include "scheme.h"
#include "port.h"

class MainWindow;


class Canvas : public QGraphicsScene
{
public:
    Canvas(MainWindow *parent);

    const static int offsetX = 260;
    const static int offsetY = 50;

    void clearAll() {
        clear();
        scheme.clear();
    }

private slots:

    void Additem(qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    void createBlock(double x, double y);
    QString getActualBlockName();
    void changeCircleColor(QGraphicsItem *item, QColor color);
    Port *getPortPtrFromItem(QGraphicsItem *item);
    MainWindow *parentWindow;
    Scheme scheme;
    QGraphicsItem *sourceItem;
    bool lineSourceValid;
    QGraphicsLineItem *tmpLine;
};

#endif // CANVAS_H
