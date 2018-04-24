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

std::vector<int> Scheme::simulateStep()
{
    if (blocks.empty()) {
        throw "empty scheme!";
    }
    if (!isSchemeComplete()) {
        throw "scheme is incomplete!";
    }
    std::vector<int> calculatedIndexes;
    std::vector<Block *> toBeCalculated;
    toBeCalculated = getReadyBlocks();
    for (Block *block : toBeCalculated) {
        block->calculate();
        qDebug() << getIdxByBlock(block);
        calculatedIndexes.push_back(getIdxByBlock(block));
    }
    return calculatedIndexes;
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
    for (int i = 0; i < block->outPortsNumber; i++) {
        Port *nextPort;
        nextPort = block->getOutPort(i)->pairedPort;
        if (nextPort && isLooped(nextPort->blockPtr,maxDepth,currentDepth)) {
            return true;
        }
    }
    return false;
}

std::vector<Block *> Scheme::getReadyBlocks()
{
    std::vector<Block *> readyBlocks;
    for (Block* block : blocks) {
        if (block->areInPortsSet()) {
            bool calculated = false;
            for (int aCalc : alreadyCalculated) {
                if (getIdxByBlock(block) == aCalc) {
                    calculated = true;
                }
            }
            if (!calculated) {
                readyBlocks.push_back(block);
                alreadyCalculated.push_back(getIdxByBlock(block));
            }
        }
    }
    return readyBlocks;
}

bool Scheme::isSchemeComplete()
{
    for (Block* block : blocks) {
        for (int i = 0; i < block->inPortsNumber; i++) {
            if (!block->getInPort(i)->isSet() && block->getInPort(i)->pairedPort == nullptr) {
                return false;
            }
        }
    }
    return true;
}

int Scheme::getIdxByBlock(Block *blockPtr)
{
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == blockPtr) {
            return i;
        }
    }
    throw "Block doesn't exist";
    return 0;
}

int Scheme::getLastBlockIndex()
{
    return blocks.size() - 1;
}

Block* Scheme::getBlock(int index)
{
    return blocks[index];
}
