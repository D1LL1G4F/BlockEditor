/*! \file      block.h
 *  \brief     header file for Block class
 *  \author    Matej Knazik
 *  \date      2018
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include "port.h"
#include <QDebug>

using namespace std;

class Port;

//!  Block class
/*!
  A backend class representing block in scheme.
*/
class Block
{
public:

    //! Constant representing out port type
    static const int PORT_OUT;
    //! Constant representing in port type
    static const int PORT_IN;


    //! Number of input ports
    int inPortsNumber;
    //! Number of output ports
    int outPortsNumber;


    //! Constructor
    /*!
      Constructs a block of specified type on coords [x,y] with
      specifiend width and height.
    */
    Block(int type, double x, double y, double width, double height);

    //! Destructor
    /*!
      Destructs block.
    */
    ~Block();


    //! Method for setting coordinates of block
    /*!
        \param double value of x coordinate
        \param double value of y coordinate
        \return void
    */
    void setCoords(double xCoord, double yCoord);
    //! Method providing calculation of block (sets output ports based
    //! on type of block and values in input ports)
    /*!
        \return void
    */
    void calculate();
    //! Method providing pointer to input port on specified index
    /*!
        \param int index of input port
        \return pointer to Port
    */
    Port* getInPort(int index);
    //! Method providing pointer to output port on specified index
    /*!
        \param int index of output port
        \return pointer to Port
    */
    Port* getOutPort(int index);
    //! Method providing type of block
    /*!
        \return int representation of type (for types see MainWindow class)
    */
    int getType();
    //! Method for setting Port value
    /*!
        \param int representation of port type (Block::PORT_IN / Block::PORT_OUT)
        \param int port index
        \param double value to be set
        \return pointer to Port
    */
    void setPort(int port_type, int port_index, double value);

    //! Method indicating whenever all inputs ports are set
    /*!
        \return bool
    */
    bool areInPortsSet();

    //! Method returning x coordinate
    /*!
        \return double value of x coord
    */
    double getX();
    //! Method returning y coordinate
    /*!
        \return double value of y coord
    */
    double getY();

private:
    //! block type
    int blockType;

    //! input ports vector
    vector<Port> inPorts;
    //! output ports vector
    vector<Port> outPorts;

    //! coords
    double x, y;

    //! height of block
    double blockHeight;
    //! width of block
    double blockWidth;
};

#endif // BLOCK_H
