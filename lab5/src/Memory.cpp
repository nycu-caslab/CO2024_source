#include "Memory.h"
#include <unordered_map>
#include <stdexcept>

struct Memory::Impl {
    std::unordered_map<unsigned int, unsigned int> *m;
    unsigned int read_cnt;
    unsigned int write_cnt;
};


Memory::Memory() {
    impl = new Impl;
    impl->m = new std::unordered_map<unsigned int, unsigned int>();
    impl->read_cnt = 0;
    impl->write_cnt = 0;
};

Memory::~Memory(){
    delete impl->m;
    delete impl;
    
}

unsigned int Memory::read(unsigned int addr) const {
    if(addr % 4 != 0)
        throw std::invalid_argument("Memory addr % 4 != 0 " + std::to_string(addr));
    impl->read_cnt++;
    return (impl->m->find(addr) == impl->m->end())? 0: impl->m->at(addr);
};

void Memory::write(unsigned int addr, unsigned int data) {
    if(addr % 4 != 0)
        throw std::invalid_argument("Memory addr % 4 != 0 " + std::to_string(addr));
    impl->write_cnt++;
    (*(impl->m))[addr] = data;
    return ;
};

std::pair<unsigned, unsigned> Memory::getUsage() const{
    return {impl->read_cnt, impl->write_cnt};
};


