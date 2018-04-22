#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include "port.h"
#include <QDebug>

using namespace std;

class Port;


class Block
{
public:

    static const int PORT_OUT;
    static const int PORT_IN;

    int inPortsNumber;
    int outPortsNumber;

    Block(int type, double x, double y, double width, double height);

    void calculate();
    Port* getInPort(int index);
    Port* getOutPort(int index);
    void setPort(int port_type, int port_index, double value);
    bool areInPortsSet();

    double getX();
    double getY();

private:
    string blockType;
    vector<Port> inPorts;
    vector<Port> outPorts;

    double x, y;
};

#endif // BLOCK_H
