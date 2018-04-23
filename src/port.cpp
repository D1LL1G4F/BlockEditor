#include "port.h"

Port::Port(string portType, Block *parentPtr, double x, double y)
{
    name = portType;
    xCoord = x;
    yCoord = y;
    blockPtr = parentPtr;
    pairedPort = nullptr;
    status = false;
}

string Port::getType()
{
    return name;
}

double Port::getValue()
{
    return value;
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
    pairedPort = nullptr;
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
