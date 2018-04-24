#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include "block.h"

class Scheme
{


public:
    Scheme();

    bool isSchemeLooped();
    std::vector<int> simulateStep();
    int getLastBlockIndex();
    Block* getBlock(int index);

    void save(std::string path);
    void load(std::string path);

    Block* addBlock(Block *block);

    void clear();

private:
    bool isLooped(Block *block, int maxDepth, int currentDepth);
    std::vector<Block *> getReadyBlocks();
    bool isSchemeComplete();
    int getIdxByBlock(Block *blockPtr);
    std::vector<Block*> recentlyCalculated;
    std::vector<Block*> uncalculated;
    std::vector<Block*> blocks;
};

#endif // SCHEME_H
