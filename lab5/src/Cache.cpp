#include "Cache.h"

Cache::Cache(unsigned int size): size{size} {
    len = size / 4;
    blocks.clear();
    blocks.resize(len, Block(4));
};

unsigned int Cache::get_size(){
    return this->size;
}

unsigned int Cache::get_len(){
    return this->len;
}

unsigned int Cache::get_machine_address_bit(){
    return 32;
}

unsigned int Cache::set_block_size(unsigned int block_size){
    if(block_size % 4 != 0)
        throw std::invalid_argument("Block size % 4 != 0");
    len = size / block_size;
    blocks.clear();
    blocks.resize(len, Block(block_size));
    return len;
}

Block& Cache::operator[](unsigned int index){
    if(index >= len)
        throw std::invalid_argument("Cache index out of bound");
    return this->blocks[index];
};
