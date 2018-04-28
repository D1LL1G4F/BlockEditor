#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <string>
#include "block.h"

using namespace std;

class Block;


class Port
{
public:
    Port(string portType, Block *parentPtr, double x, double y);

    string name;
    double value;

    Block *blockPtr;
    Port *pairedPort;

    bool isSet();
    string getType();
    double getValue();
    void setCoords(double x, double y);
    double getX();
    double getY();
    void set(double val);
    void unset();
    bool isIn();
    bool isOut();
private:
    bool status;
    double xCoord;
    double yCoord;
};

#endif // PORT_H
