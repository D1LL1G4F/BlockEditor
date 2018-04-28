#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <vector>
#include "mainwindow.h"
#include "scheme.h"
#include "port.h"

#include <boost/property_tree/ptree.hpp>

namespace json = boost::property_tree;

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
    Scheme* getScheme();
    void changeRectColor(int idx, QColor color);
    void setScheme(json::ptree root);

private slots:

    void Additem(qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    void createBlock(double x, double y);
    QString getActualBlockName(int type);
    void changeCircleColor(QGraphicsItem *item, QColor color);
    Port *getPortPtrFromItem(QGraphicsItem *item);
    void reloadScheme();
    MainWindow *parentWindow;
    Scheme scheme;
    QGraphicsItem *sourceItem;
    std::vector<QGraphicsItem*> blockItems;
    bool lineSourceValid;
    QGraphicsLineItem *tmpLine;


};

#endif // CANVAS_H
