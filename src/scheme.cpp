/*! \file      scheme.cpp
 *  \brief     contains definitions of Scheme class methods
 *  \author    Matej Knazik
 *  \date      2018
 */

#include "scheme.h"

namespace json = boost::property_tree;

#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 125

Scheme::Scheme()
{

}

Scheme::~Scheme()
{
    alreadyCalculated.clear();
    blocks.clear();
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
        throw "scheme is incomplete! (set undefined port (red circles) with right click)";
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

void Scheme::removeBLock(int idx)
{
    Block *b;
    b = getBlock(idx);
    if (!b)
        return;
    for (int i = 0; i < b->inPortsNumber; i++) {
        Port *p;
        p = b->getInPort(i);
        if (p->pairedPort)
            p->pairedPort->pairedPort = nullptr;
    }
    for (int i = 0; i < b->outPortsNumber; i++) {
        Port *p;
        p = b->getOutPort(i);
        if (p->pairedPort)
            p->pairedPort->pairedPort = nullptr;
    }
    blocks.erase(blocks.begin()+idx);
}

void Scheme::removeLinkOnPort(double x, double y)
{
    Port *p;
    p = getPortByCoords(x,y);
    if (!p)
        return;
    if (p->pairedPort)
        p->pairedPort->pairedPort = nullptr;
    p->pairedPort = nullptr;
}

void Scheme::clear() {
    blocks.clear();
    alreadyCalculated.clear();
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

Port *Scheme::getPortByCoords(double x, double y)
{
    for (Block* b : blocks) {
        for (int i = 0; i < b->outPortsNumber; i++) {
            Port *outP;
            outP = b->getOutPort(i);
            double xOff = fabs(x - outP->getX());
            double yOff = fabs(y - outP->getY());
            if (xOff < 0.05 && yOff < 0.05 ) {
                return outP;
            }
        }
        for (int i = 0; i < b->inPortsNumber; i++) {
            Port *inP;
            inP = b->getInPort(i);
            double xOff = fabs(x - inP->getX());
            double yOff = fabs(y - inP->getY());
            if (xOff < 0.05 && yOff < 0.05 ) {
                return inP;
            }
        }
    }
    return nullptr;
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
        json::ptree inPorts;
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
            inPorts.push_back(std::make_pair("Port", p));
        }
        b.add_child("inputPorts",inPorts);
        json::ptree outPorts;
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
            outPorts.push_back(std::make_pair("Port", p));
        }
        b.add_child("outputPorts",outPorts);
        //
        blockNodes.push_back(std::make_pair("block", b));
    }
    root.add_child("Blocks", blockNodes);
    return root;
}

void Scheme::loadScheme(boost::property_tree::ptree root)
{
    blocks.clear();
    alreadyCalculated.clear();

    for (json::ptree::value_type &blockNode : root.get_child("Blocks")) { // create blocks
        int blockType;
        double x;
        double y;

        blockType = blockNode.second.get<int>("blockType");
        x = blockNode.second.get<double>("x");
        y = blockNode.second.get<double>("y");
        Block *b;
        b = addBlock(new Block(blockType,x,y,BLOCK_WIDTH,BLOCK_HEIGHT));
        int iter = 0;
        for (json::ptree::value_type &inPortNode : blockNode.second.get_child("inputPorts")) {
            if (inPortNode.second.get<bool>("status")) {
                b->getInPort(iter)->set(inPortNode.second.get<double>("value"));
            }
            iter++;
        }
    }
    int blckIter = 0;
    for (json::ptree::value_type &blockNode : root.get_child("Blocks")) { // add pointers to ports
        Block *b;
        b = getBlock(blckIter);
        int portIter = 0;
        for (json::ptree::value_type &inPortNode : blockNode.second.get_child("inputPorts")) {
            Port *p;
            p = b->getInPort(portIter);
            double pairedX = inPortNode.second.get<double>("pairedPortX");
            double pairedY = inPortNode.second.get<double>("pairedPortY");
            if (pairedX > 0 && pairedY > 0) {
                p->pairedPort = getPortByCoords(pairedX, pairedY);
            }
            portIter++;
        }
        portIter = 0;
        for (json::ptree::value_type &outPortNode : blockNode.second.get_child("outputPorts")) {
            Port *p;
            p = b->getOutPort(portIter);
            double pairedX = outPortNode.second.get<double>("pairedPortX");
            double pairedY = outPortNode.second.get<double>("pairedPortY");
            if (pairedX > 0 && pairedY > 0) {
                p->pairedPort = getPortByCoords(pairedX, pairedY);
            }
            portIter++;
        }
        blckIter++;
    }

}
