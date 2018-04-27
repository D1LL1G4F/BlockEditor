#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include "block.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace json = boost::property_tree;

class Scheme
{


public:
    Scheme();

    bool isSchemeLooped();
    std::vector<int> simulateStep();
    void resetSimulation();
    int getLastBlockIndex();
    bool isSimulationFinished();
    Block* getBlock(int index);

    json::ptree serializeToJson();

    Block* addBlock(Block *block);

    void clear();

private:
    bool isLooped(Block *block, int maxDepth, int currentDepth);
    std::vector<Block *> getReadyBlocks();
    bool isSchemeComplete();
    int getIdxByBlock(Block *blockPtr);
    std::vector<int> alreadyCalculated;
    std::vector<Block*> blocks;
};

#endif // SCHEME_H
