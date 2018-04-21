#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include "block.h"

class Scheme
{
    std::vector<Block> blocks;

public:
    Scheme();

    bool stepOne();
    void stepAll();

    void save(std::string path);
    void load(std::string path);

    Block& addBlock(const Block &block);

    void clear();
};

#endif // SCHEME_H
