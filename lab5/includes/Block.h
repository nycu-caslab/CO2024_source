#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <vector>

class Block{
private:
    std::vector<unsigned int> values;
public:
    unsigned int len;
    unsigned int tag;
    
    Block(unsigned int block_size);

    unsigned int& operator[](unsigned int index);
};

#endif