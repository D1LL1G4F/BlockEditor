#include "linker.h"

Linker::Linker(Port *source, Port *destination)
{
    srcPort = source;
    source->set(0);
    destPort = destination;
    destination->set(0);
}
