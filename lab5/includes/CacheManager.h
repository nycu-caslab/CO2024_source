#pragma once

#include "Cache.h"
#include "Memory.h"


class CacheManager
{
private:
/*
* 1. TAs' simulator will check if you store data in cache or not,
*    so make sure that you use cache correctly 
* 2. When cache miss, you should call memory to get data.
* 3. Don't modify original member function and variable, however, 
*    you are allow to declare addtional ones. 
* 4. Follow rules above, otherwise, you will get failed in this lab. 
*/
    Memory *memory;
    Cache *cache;
    unsigned int size;       // bytes
    unsigned int tag_bits;
public:

    CacheManager(Memory *memory, Cache *cache);
    ~CacheManager();
    unsigned int read(unsigned int addr);
    void write(unsigned int addr, unsigned value);
};
