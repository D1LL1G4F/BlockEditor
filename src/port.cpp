/*! \file      port.cpp
 *  \brief     contains definitions of port class methods
 *  \author    Matej Knazik
 *  \date      2018
 */

#include "port.h"

Port::Port(string portType, Block *parentPtr, double x, double y)
{
    name = portType;
    xCoord = x;
    yCoord = y;
    blockPtr = parentPtr;
    pairedPort = nullptr;
    status = false;
    value = 0;
}

Port::~Port()
{

}

string Port::getType()
{
    return name;
}

double Port::getValue()
{
    return value;
}

void Port::setCoords(double x, double y)
{
    xCoord = x;
    yCoord = y;
}

double Port::getX()
{
    return xCoord;
}

double Port::getY()
{
    return yCoord;
}

bool Port::isSet()
{
    return status;
}

void Port::set(double val)
{
    value = val;
    status = true;
}

void Port::unset()
{
    status = false;
    value = 0;
}

bool Port::isIn()
{
    for (int i = 0; i < blockPtr->inPortsNumber; i++) {
        if (blockPtr->getInPort(i)->getX() == xCoord && blockPtr->getInPort(i)->getY() == yCoord)
            return true;
    }
    return false;
}

bool Port::isOut()
{
    for (int i = 0; i < blockPtr->outPortsNumber; i++) {
        if (blockPtr->getOutPort(i)->getX() == xCoord && blockPtr->getOutPort(i)->getY() == yCoord)
            return true;
    }
    return false;
}
