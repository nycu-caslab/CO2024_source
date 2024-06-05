#pragma once

#include "Cache.h"
#include "Memory.h"
#include <iostream>
#include <cmath>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;


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
    unsigned int cache_way = 1;
    unsigned int block_size = 4;
    unsigned int block_size_bit;
    unsigned int index_bit;
    unsigned int set_num;
    vector<deque<char>> cache_line;
    vector<bool> dirty;
    CacheManager(Memory *memory, Cache *cache);


    deque<char> ::iterator find_value(deque<char> *v, char x);

    bool check_cache(unsigned int addr, char* pos_in_cache_line);

    unsigned int read(unsigned int addr);

    void write(unsigned int addr, unsigned int value);

    unsigned int get_tag_bits();
};