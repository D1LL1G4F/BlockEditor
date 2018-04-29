/*! \file      port.h
 *  \brief     header file for Block class
 *  \author    Matej Knazik
 *  \date      2018
 */

#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <string>
#include "block.h"

using namespace std;

class Block;

//!  Port class
/*!
  A backend class representing port inside block.
*/
class Port
{
public:
    //! Constructor
    /*!
        constuct Port
    */
    Port(string portType, Block *parentPtr, double x, double y);
    //! Destructor
    /*!
        destructs Port
    */
    ~Port();

    //! pointer to parent Block
    Block *blockPtr;
    //! pointer to linked Port
    Port *pairedPort;

    //! Method indicating whenever Port is set
    /*!
        \return bool
    */
    bool isSet();

    //! Retrurns type of Port
    /*!
        \return string name of type
    */
    string getType();

    //! Retrurns type of Port
    /*!
        \return double of port's value
    */
    double getValue();

    //! Set coordinates of Port
    /*!
        \return void
    */
    void setCoords(double x, double y);

    //! get x coord
    /*!
        \return double value of x coordinate
    */
    double getX();

    //! get y coord
    /*!
        \return double value of y coordinate
    */
    double getY();

    //! method for setting value of port
    /*!
        \return void
    */
    void set(double val);

    //! method for unsetting port value
    /*!
        \return void
    */
    void unset();

    //! Method indicating whenever Port is input port
    /*!
        \return bool
    */
    bool isIn();

    //! Method indicating whenever Port is output port
    /*!
        \return bool
    */
    bool isOut();


private:
    //! status indicates if port is set or not
    bool status;
    //! x coordinate of port
    double xCoord;
    //! y coordinate of port
    double yCoord;
    //! port type
    string name;
    //! port value
    double value;
};

#endif // PORT_H
