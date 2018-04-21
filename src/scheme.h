#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include "block.h"

class Scheme
{
    std::vector<Block> blocks;

public:
    Scheme();

    void stepOne();
    void stepAll();

    void save(std::string path);
    void load(std::string path);

    void addBlock(Block &block);
    void removeBlock(Block &block);
};

#endif // SCHEME_H
