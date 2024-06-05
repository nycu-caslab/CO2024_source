#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>


#include "CacheManager.h"
#include "Memory.h"
#include "Cache.h"

class Evaluator
{
private:
    unsigned int cache_size;
    std::string filepath;

public:
    Evaluator(unsigned cache_size, std::string filepath);
    
    void run();    

};


