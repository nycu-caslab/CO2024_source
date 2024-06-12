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
    std::ifstream infile(filepath);
    std::string line;

    std::cout << "cache total_size : " << cache.get_size() << std::endl; 
    std::cout << "cache entry_size : " << cache.get_size()/cache.get_len() << std::endl;
    std::cout << "cache length     : " << cache.get_len() << std::endl; 
    std::cout << "block total_size : " << cache.get_size()/cache.get_len() << std::endl; 
    std::cout << "block entry_size : " << cache.get_size()/cache.get_len()/cache[0].len << std::endl; 
    std::cout << "block length     : " << cache[0].len << std::endl; 


    int op_cnt = 0, miss_cnt = 0;
    int read_req = 0;
    int write_req = 0;
    while(std::getline(infile, line)){
        std::istringstream iss(line);
        std::string word;
        char rw;
        iss >> rw >> word;
        unsigned int addr = std::stoul(word, nullptr, 16);
        if(rw == 'r'){
            read_req++;

            auto before_find_usage = mem.getUsage();
            auto expected_hit      = cache_manager.find(addr) != nullptr;
            auto after_find_usage  = mem.getUsage();
            
            if(before_find_usage != after_find_usage){
                std::cerr << "You can't access memory in CacheManager.find()!" << std::endl;
                return ;
            }

            unsigned int gt = golden.read(addr);

            auto [before_read, before_write] = mem.getUsage();
            unsigned int value = cache_manager.read(addr);
            auto [after_read, after_write] = mem.getUsage();

            if(gt != value){
                std::cerr << "Wrong read, expect: " << std::hex << gt << " received: " << value  << " at(" << addr << ")" << std::endl;
                return ;
            }
            
            if(expected_hit == 0 && before_read == after_read){
                std::cerr << "Expect a read miss at(" << std::hex << addr << ") however you didn't read memory. Do you store data in cache correctly?" << std::endl;
                return ;
            }

            if(expected_hit == 1 && before_read != after_read){
                std::cerr << "CacheManager.find() return addr " << std::hex << addr << " is in cache, however you access memory in later CacheManager.read()" << std::endl;
                return ;
            }

            miss_cnt += (expected_hit == 0);
        }
        else if(rw == 'w'){
            write_req++;
            iss >> word;
            unsigned int value = std::stoul(word, nullptr, 16);

            auto before_find_usage = mem.getUsage();
            auto expected_hit      = cache_manager.find(addr) != nullptr;
            auto after_find_usage  = mem.getUsage();
            if(before_find_usage != after_find_usage){
                std::cerr << "You can't access memory in find function!" << std::endl;
                return ;
            }

            golden.write(addr, value);

            auto before = mem.getUsage();
            cache_manager.write(addr, value);
            auto after = mem.getUsage();

            if(expected_hit == 0 && before == after){
                std::cerr << "Expect a write miss at(" << std::hex << addr << ") however you did't access memory, Do you store data in cache correctly?" << std::endl;
                return ;
            }

            miss_cnt += (expected_hit == 0);

        }
        op_cnt++;
    }

    auto [read_cnt, write_cnt] = mem.getUsage();
    std::cout << "--- --- result --- ---\n";
    std::cout << "read_reqs: " << read_req << " write_reqs: " << write_req << std::endl;
    std::cout << "mem_reads: " << read_cnt << " mem_writes: " << write_cnt << "\n";
    std::cout << "miss: " << miss_cnt << "\n";
    return ;
}
