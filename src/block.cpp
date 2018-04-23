#include "block.h"
#include "mainwindow.h"
#include <iostream>
#include <string>

using namespace std;

const int Block::PORT_OUT = 0;
const int Block::PORT_IN = 1;


Block::Block(int type, double x, double y, double width, double height)
    : x(x), y(y)
{
   blockType = type;
   inPortsNumber = 2;
   outPortsNumber = 1;

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

double Block::getX() {
    return x;
}

double Block::getY() {
    return y;
}

void Block::calculate()
{
    // TODO
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


