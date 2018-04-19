#include "block.h"
#include <iostream>
#include <string>

using namespace std;

const int Block::PORT_OUT = 0;
const int Block::PORT_IN = 1;


Block::Block(string type, int inPortsN, int outPortsN)
{
   BlockType = type;
   inPortsNumber = inPortsN;
   outPortsNumber = outPortsN;
   string portType("AND"); // TODO

   // create input ports
   for (int i = 0; i < inPortsN; i++) {
       inPorts.push_back(new Port(portType,this));
   }

    // create ouput ports
   for (int i = 0; i < outPortsN; i++) {
       outPorts.push_back(new Port(portType,this));
   }
}

void Block::calculate()
{
    // TODO
}

Port* Block::getInPort(int index)
{
    if (index < inPortsNumber && index >= 0) {
        return inPorts[index];
    } else {
        return nullptr;
    }
}

Port* Block::getOutPort(int index)
{
    if (index < outPortsNumber && index >= 0) {
        return outPorts[index];
    } else {
        return nullptr;
    }
}

void Block::setPort(int port_type, int port_index, double value)
{
    switch (port_type) {
    case PORT_OUT:
        if (port_index < outPortsNumber && port_index >= 0) {
            outPorts[port_index]->set(value);
        }
        break;
    case PORT_IN:
        if (port_index < inPortsNumber && port_index >= 0) {
            inPorts[port_index]->set(value);
        }
        break;
    default:
        break;
    }
}

bool Block::areInPortsSet()
{
    for(auto port : inPorts) {
        if (!port->isSet()){
            return false;
        }
    }
    return true;
}


