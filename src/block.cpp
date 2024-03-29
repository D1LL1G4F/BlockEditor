/*! \file      block.cpp
 *  \brief     contains definitions of block class methods
 *  \author    Matej Knazik
 *  \date      2018
 */

#include "block.h"
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int Block::PORT_OUT = 0;
const int Block::PORT_IN = 1;


Block::Block(int type, double x, double y, double width, double height)
    : x(x), y(y)
{
   blockType = type;
   inPortsNumber = 2;
   outPortsNumber = 1;
   blockHeight = height;
   blockWidth = width;

   string portTypeIn, portTypeOut;

   switch (type) {
   case MainWindow::ITEM_AND:
   case MainWindow::ITEM_NAND:
   case MainWindow::ITEM_OR:
   case MainWindow::ITEM_XOR:
       portTypeIn = "logical";
       portTypeOut = "logical";
       break;
   case MainWindow::ITEM_ADD:
   case MainWindow::ITEM_SUB:
       portTypeIn = "decimal";
       portTypeOut = "decimal";
       break;
   case MainWindow::ITEM_LT:
   case MainWindow::ITEM_GT:
       portTypeIn = "decimal";
       portTypeOut = "logical";
       break;
   default:
       break;
   }

   // create input ports
   for (int i = 0; i < inPortsNumber; i++) {
       inPorts.push_back(Port(portTypeIn,this,x+8,y + (height/inPortsNumber)*(i+0.5)));
   }


    // create ouput ports
   for (int i = 0; i < outPortsNumber; i++) {
       outPorts.push_back(Port(portTypeOut,this,x+width-20,y + (height/outPortsNumber)*(i+0.5)));
   }
}

Block::~Block()
{
    inPorts.clear();
    outPorts.clear();
}

void Block::setCoords(double xCoord, double yCoord)
{
    x = xCoord;
    y = yCoord;
    for (int i = 0; i < inPortsNumber; i++) {
        getInPort(i)->setCoords(x+8,y + (blockHeight/inPortsNumber)*(i+0.5));
    }
    for (int i = 0; i < outPortsNumber; i++) {
        getOutPort(i)->setCoords(x+blockWidth-20,y + (blockHeight/outPortsNumber)*(i+0.5));
    }

}

double Block::getX() {
    return x;
}

double Block::getY() {
    return y;
}

void Block::calculate()
{
    switch (blockType) {
    case MainWindow::ITEM_AND:
        outPorts[0].set(inPorts[0].getValue() && inPorts[1].getValue());
        break;
    case MainWindow::ITEM_NAND:
        outPorts[0].set(!(inPorts[0].getValue() && inPorts[1].getValue()));
        break;
    case MainWindow::ITEM_OR:
        outPorts[0].set(inPorts[0].getValue() || inPorts[1].getValue());
        break;
    case MainWindow::ITEM_XOR:
        outPorts[0].set(fabs(inPorts[0].getValue() - inPorts[1].getValue()) > 0.5);
        break;
    case MainWindow::ITEM_ADD:
        outPorts[0].set(inPorts[0].getValue() + inPorts[1].getValue());
        break;
    case MainWindow::ITEM_SUB:
        outPorts[0].set(inPorts[0].getValue() - inPorts[1].getValue());
        break;
    case MainWindow::ITEM_LT:
        outPorts[0].set(inPorts[0].getValue() < inPorts[1].getValue());
        break;
    case MainWindow::ITEM_GT:
        outPorts[0].set(inPorts[0].getValue() > inPorts[1].getValue());
        break;
    default:
        break;
    }

    for (Port port : outPorts) {
        if (port.pairedPort) {
            port.pairedPort->set(port.getValue());
        }
    }
}

Port* Block::getInPort(int index)
{
    if (index < inPortsNumber && index >= 0) {
        return &inPorts[index];
    } else {
        qDebug() << "port out of index in getInPort()\n";
        return nullptr;
    }
}

Port* Block::getOutPort(int index)
{
    if (index < outPortsNumber && index >= 0) {
        return &outPorts[index];
    } else {
        qDebug() << "port out of index in getOutPort()\n";
        return nullptr;
    }
}

int Block::getType()
{
    return blockType;
}

void Block::setPort(int port_type, int port_index, double value)
{
    switch (port_type) {
    case PORT_OUT:
        if (port_index < outPortsNumber && port_index >= 0) {
            outPorts[port_index].set(value);
        }
        break;
    case PORT_IN:
        if (port_index < inPortsNumber && port_index >= 0) {
            inPorts[port_index].set(value);
        }
        break;
    default:
        break;
    }
}

bool Block::areInPortsSet()
{
    for (auto port : inPorts) {
        if (!port.isSet()){
            return false;
        }
    }
    return true;
}


