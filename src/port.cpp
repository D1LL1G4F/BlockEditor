#include "port.h"

Port::Port(string portType, Block *parentPtr)
{
    name = portType;
    blockPtr = parentPtr;
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

bool Port::isSet()
{
    return status;
}

void Port::set(double val)
{
    value = val;
    status = true;
}
