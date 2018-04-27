#include "scheme.h"

namespace json = boost::property_tree;

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

void Scheme::resetSimulation()
{
    for (Block* block : blocks) {
        for (int i = 0; i < block->outPortsNumber; i++) {
            block->getOutPort(i)->unset();
        }
        for (int i = 0; i < block->inPortsNumber; i++) {
            Port *inPort;
            inPort = block->getInPort(i);
            if (inPort->pairedPort != nullptr) {
                inPort->unset();
            }
        }
    }
    alreadyCalculated.clear();
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

bool Scheme::isSimulationFinished()
{
    return blocks.size() == alreadyCalculated.size();
}

Block* Scheme::getBlock(int index)
{
    return blocks[index];
}

json::ptree Scheme::serializeToJson()
{
    json::ptree root;
    json::ptree blockNodes;
    for (Block* block : blocks) {
        json::ptree b;
        //
        b.put("inPortsNumber",block->inPortsNumber);
        b.put("outPortsNumber",block->outPortsNumber);
        b.put("blockType",block->getType());
        b.put("x",block->getX());
        b.put("y",block->getY());
        for (int i = 0; i < block->inPortsNumber; i++) {
            Port *port;
            port = block->getInPort(i);
            json::ptree p;
            //
            p.put("type",port->getType());
            p.put("value",port->getValue());
            p.put("status",port->isSet());
            p.put("x",port->getX());
            p.put("y",port->getY());
            if (port->pairedPort) {
                p.put("pairedPortX",port->pairedPort->getX());
                p.put("pairedPortY",port->pairedPort->getY());
            } else {
                p.put("pairedPortX",-1);
                p.put("pairedPortY",-1);
            }
            //
            b.push_back(std::make_pair("inputPort", p));
        }
        for (int i = 0; i < block->outPortsNumber; i++) {
            Port *port;
            port = block->getOutPort(i);
            json::ptree p;
            //
            p.put("type",port->getType());
            p.put("value",port->getValue());
            p.put("status",port->isSet());
            p.put("x",port->getX());
            p.put("y",port->getY());
            if (port->pairedPort) {
                p.put("pairedPortX",port->pairedPort->getX());
                p.put("pairedPortY",port->pairedPort->getY());
            } else {
                p.put("pairedPortX",-1);
                p.put("pairedPortY",-1);
            }
            //
            b.push_back(std::make_pair("outputPort", p));
        }
        //
        blockNodes.push_back(std::make_pair("block", b));
    }
    root.add_child("Blocks", blockNodes);
    return root;
}
