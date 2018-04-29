/*! \file      canvas.h
 *  \brief     header file for Canvas class
 *  \author    Matej Knazik
 *  \date      2018
 */

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

//!  Canvas class
/*!
  A frontend class representing Canvas (derivate of QGraphicScene).
*/
class Canvas : public QGraphicsScene
{

public:

    //! Constructor
    /*!
      Constructor for Canvas.
      \param parent pointer
    */
    Canvas(MainWindow *parent);

    //! Clears whole canvas
    /*!
      \return void
    */
    void clearAll();

    //! Repaints canvas based on scheme
    /*!
      \return void
    */
    void reloadScheme();

    //! Method for getting Scheme pointer
    /*!
      \return pointer to Scheme
    */
    Scheme* getScheme();

    //! changes color of Rectange on certain index
    /*!
      \param int index of rectangle to change
      \param color
      \return void
    */
    void changeRectColor(int idx, QColor color);

    //! method for setting new scheme
    /*!
      \param JSON root of scheme
      \return void
    */
    void setScheme(json::ptree root);

private slots:

    //! add new block
    /*!
      \param x coord
      \param y coord
      \return void
    */
    void Additem(qreal x, qreal y);

protected:
    //! override mousePressEvent
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    //! override mouseReleaseEvent
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    //! override mouseMoveEvent
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    //! creates new block
    void createBlock(double x, double y);
    //! gets block name
    QString getActualBlockName(int type);
    //! changes circle color
    void changeCircleColor(QGraphicsItem *item, QColor color);
    //! gets port pointer by its item in cavas
    Port *getPortPtrFromItem(QGraphicsItem *item);

    //! parent window
    MainWindow *parentWindow;
    //! current scheme
    Scheme scheme;
    //! source item when creating new linker
    QGraphicsItem *sourceItem;
    //! vector of block items (indexes corresponds with blocks in scheme)
    std::vector<QGraphicsItem*> blockItems;
    //! indicates if linker can be draw
    bool lineSourceValid;
    //! temporary line while draging linker
    QGraphicsLineItem *tmpLine;
    //! block pointer for moving blocks
    Block *movingBlock;


};

#endif // CANVAS_H
