#include "scheme.h"

Scheme::Scheme()
{

}

Block* Scheme::addBlock(const Block &block) {
    blocks.push_back(block);

    return &blocks.back();
}

void Scheme::clear() {
    blocks.clear();
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
    return &blocks[index];
}

bool Scheme::stepOne() {
    return false;
}
