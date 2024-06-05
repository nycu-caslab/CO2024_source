#include "Evaluator.h"
#include <math.h>

Evaluator::Evaluator(unsigned int cache_size, std::string filepath):
    cache_size{cache_size}, filepath{filepath}
{
    return ;
}

void Evaluator::run(){
    Memory golden;
    Memory mem;
    Cache cache(cache_size);
    CacheManager cache_manager(&mem, &cache);
    unsigned int tag_bits = 32 - log2(cache.get_len()) - log2(cache.get_size()/cache.get_len());
    std::ifstream infile(filepath);
    std::string line;

    int op_cnt = 0, miss_cnt = 0;
    while(std::getline(infile, line)){
        std::istringstream iss(line);
        std::string word;
        char rw;
        iss >> rw >> word;
        unsigned int addr = std::stoul(word, nullptr, 16);
        if(rw == 'r'){
            unsigned int pread, read, pwrite, write;
            mem.getUsage(pread, pwrite);

            unsigned int target_tag = addr >> (32 - tag_bits); // get the leftmost bits as tag; 
            bool expected_hit = 0;
            for(unsigned i=0; i<cache.get_len(); ++i){
                if(cache[i].tag == target_tag){
                    expected_hit = 1;
                    break;
                }
            }

            unsigned int gt = golden.read(addr);
            unsigned int value = cache_manager.read(addr);
            mem.getUsage(read, write);

            if(gt != value){
                std::cerr << "Wrong read, expect: " << std::hex << gt << " received: " << value  << " at(" << addr << ")" << std::endl;
                return ;
            }
            else if(expected_hit == 0 && pread == read){
                std::cerr << "Expect a read miss at(" << std::hex << addr << ") however you didn't read memory. Do you store data in cache correctly?" << std::endl;
                return ;
            }
            miss_cnt += !expected_hit;
        }
        else if(rw == 'w'){
            iss >> word;
            unsigned int value = std::stoul(word, nullptr, 16);

            golden.write(addr, value);
            cache_manager.write(addr, value);
        }
        op_cnt++;
    }

    unsigned int read_cnt, write_cnt;
    mem.getUsage(read_cnt, write_cnt);
    std::cout << "reads: " << read_cnt << " writes: " << write_cnt << "\n";
    std::cout << "miss: " << miss_cnt << "\n";
    return ;
}
