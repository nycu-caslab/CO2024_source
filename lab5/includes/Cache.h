#ifndef __CACHE_H__
#define __CACHE_H__

#include <stdexcept>
#include <vector>
#include "Block.h"


class Cache
{
private:
    std::vector<Block> blocks;
    const unsigned int size;
    unsigned int len;
public:
    Cache(unsigned int size);   
    
    unsigned int get_size();
    unsigned int get_len();
    unsigned int set_block_size(unsigned int block_size);
    unsigned int get_machine_address_bit();
    
    Block& operator[](unsigned int index);
};

#endif