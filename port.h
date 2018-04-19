#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <string>
#include "block.h"

using namespace std;


class Port
{
public:
    Port(string portType);

    string name;
    double value;

    Block *blockPtr;


    bool isSet();
    string getType();
    double getValue();
    void set(double val);
private:
    bool status;
};

#endif // PORT_H
