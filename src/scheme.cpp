#include "scheme.h"

Scheme::Scheme()
{

}

Block& Scheme::addBlock(const Block &block) {
    blocks.push_back(block);

    return blocks.back();
}

void Scheme::clear() {
    blocks.clear();
}

void Scheme::stepAll() {
    while (stepOne());
}

bool Scheme::stepOne() {
    return false;
}
