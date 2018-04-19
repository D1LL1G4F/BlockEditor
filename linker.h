#ifndef LINKER_H
#define LINKER_H

#include "port.h"


class Linker
{
public:
    Port *srcPort;
    Port *destPort;
    Linker();
};

#endif // LINKER_H
