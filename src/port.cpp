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
