#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include "block.h"

class Scheme
{
private:
    std::vector<Block*> blocks;

public:
    Scheme();

    bool stepOne();
    void stepAll();
    int getLastBlockIndex();
    Block* getBlock(int index);

    void save(std::string path);
    void load(std::string path);

    Block* addBlock(Block *block);

    void clear();
};

#endif // SCHEME_H
