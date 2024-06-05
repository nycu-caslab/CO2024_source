#include "CacheManager.h"
#include <math.h>

CacheManager::CacheManager(Memory *memory, Cache *cache){
    // TODO: implement your constructor here
    // TODO: set tag_bits accord to your design.
    // Hint: you can access cache size by cache->get_size();
    // Hint: you need to call cache->set_block_size();
    this->memory = memory;
    this->cache = cache;
    size = cache->get_size();
    cache->set_block_size(4);
    tag_bits = 32 - log2(cache->get_len()) - 2;
};

unsigned int CacheManager::read(unsigned int addr){
    // TODO:: implement replacement policy and return value 
    unsigned int index_bit = int(log2(cache->get_len()));
    unsigned int index = (addr >> 2) % cache->get_len(); 
    unsigned int tag = addr >> index_bit >> 2;

    if((*cache)[index].tag == tag)
        return (*cache)[index][0];
    (*cache)[index].tag = tag;
    return (*cache)[index][0] = memory->read(addr);
};

void CacheManager::write(unsigned int addr, unsigned value){
    // TODO:: write value to addr
    unsigned int index_bit = int(log2(cache->get_len()));
    unsigned int index = (addr >> 2) % cache->get_len(); 
    unsigned int tag = addr >> index_bit >> 2;

    if((*cache)[index].tag == tag)
        (*cache)[index][0] = value;
    memory->write(addr, value);
};

