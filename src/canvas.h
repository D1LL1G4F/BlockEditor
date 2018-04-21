#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include "mainwindow.h"

class MainWindow;


class Canvas : public QGraphicsScene
{
public:
    Canvas(MainWindow *parent);

private slots:

    void Additem(qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    MainWindow *parentWindow;
};

#endif // CANVAS_H
