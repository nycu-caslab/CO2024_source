
#include <stdexcept>
#include "Block.h"

Block::Block(unsigned int block_size){
    if(block_size % 4 != 0)
        throw std::invalid_argument("Block Size % 4 != 0");
    len = block_size / 4;
    values.resize(block_size / 4);
}


unsigned int& Block::operator[](unsigned int index){
    return this->values[index];
}