/*! \file      linker.h
 *  \brief     header file for Linker class
 *  \author    Matej Knazik
 *  \date      2018
 */

#ifndef LINKER_H
#define LINKER_H

#include "port.h"
#include <QGraphicsLineItem>
#include <QLabel>
#include <QString>

//!  Linker class
/*!
  A frontend class representing Linker on canvas (derivate of QGraphicLineItem class).
*/
class Linker : public QGraphicsLineItem
{
public:

    //! Constructor
    /*!
      Constructs a Linker on canvas from coords [x1,y2] to coords [x2,y2]
      and establishes backed connection between source port and dest port
      \param QLabel output screen where values on hover are printed
      \param first pointer to Port
      \param second pointer to Port
      \param x1
      \param y1
      \param x2
      \param y2
      \param parent item
    */
    Linker(QLabel *output,Port *source, Port *dest, qreal x1, qreal y1, qreal x2, qreal y2 ,QGraphicsItem *parent = Q_NULLPTR);
protected:
    //! overide of hoverEnterEvent
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) Q_DECL_OVERRIDE;
    //! override of hoverLeaveEvent
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) Q_DECL_OVERRIDE;

private:
    //! pointer to output port
    Port *srcPort;
    //! pointer to input port
    Port *destPort;

    //! message on output
    QGraphicsTextItem *dialogTxt;

    //! output screen Label
    QLabel *outputScr;

    //! temporay saved previous message on output
    QString prevOutput;
};

#endif // LINKER_H
