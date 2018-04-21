#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include "mainwindow.h"
#include "scheme.h"

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

private:
    MainWindow *parentWindow;
    Scheme scheme;
};

#endif // CANVAS_H
