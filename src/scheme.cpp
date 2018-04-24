#include "scheme.h"

Scheme::Scheme()
{

}

bool Scheme::isSchemeLooped()
{
    for (Block* block : blocks) {
        if (isLooped(block,blocks.size(),0))
            return true;
    }
    return false;
}

Block* Scheme::addBlock(Block *block) {
    blocks.push_back(block);

    return blocks.back();
}

void Scheme::clear() {
    blocks.clear();
}

bool Scheme::isLooped(Block *block, int maxDepth,int currentDepth)
{
    currentDepth++;
    if (currentDepth > maxDepth) {
        return true;
    }
    for (int i = 0; i < block->inPortsNumber; i++) {
        Port *nextPort;
        nextPort = block->getInPort(i)->pairedPort;
        if (nextPort && isLooped(nextPort->blockPtr,maxDepth,currentDepth)) {
            return true;
        }
    }
    for (int i = 0; i < block->outPortsNumber; i++) {
        Port *nextPort;
        nextPort = block->getOutPort(i)->pairedPort;
        if (nextPort && isLooped(nextPort->blockPtr,maxDepth,currentDepth)) {
            return true;
        }
    }
    return false;
}

void Scheme::stepAll() {
    while (stepOne());
}

int Scheme::getLastBlockIndex()
{
    return blocks.size() - 1;
}

Block* Scheme::getBlock(int index)
{
    return blocks[index];
}

bool Scheme::stepOne() {
    return false;
}
