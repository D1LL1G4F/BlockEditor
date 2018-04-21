#include "scheme.h"

Scheme::Scheme()
{

}

void Scheme::addBlock(const Block &block) {
    blocks.push_back(block);
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
