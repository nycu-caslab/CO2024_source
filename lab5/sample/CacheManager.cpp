#include "CacheManager.h"

CacheManager::CacheManager(Memory *memory, Cache *cache){
    // TODO: implement your constructor here
    // TODO: set tag_bits accord to your design.
    // Hint: you can access cache size by cache->get_size();
    // Hint: you need to call cache->set_block_size();
    this->memory = memory;
    this->cache = cache;
    cache->set_block_size(this->block_size);
    this->set_num = cache->get_len()/this->cache_way;
    this->block_size_bit = (unsigned int)log2(this->block_size);
    this->index_bit = (unsigned int)log2(this->set_num);
    this->tag_bits = cache->get_machine_address_bit() - this->block_size_bit - this->index_bit;
    this->cache_line.resize(this->set_num);
    for(unsigned int i=0; i<this->set_num; i++){
        this->cache_line[i].resize(this->cache_way);
        this->cache_line[i].clear();
    }
    this->dirty.clear();
    this->dirty.resize(cache->get_len(), 0);
};

deque<char> ::iterator CacheManager::find_value(deque<char> *v, char x){
    deque<char> ::iterator in= find(v->begin(), v->end(), x);
    return in;
}

bool CacheManager::check_cache(unsigned int addr, char* pos_in_cache_line){
    int index = (addr & (((1 << this->index_bit) - 1) << this->block_size_bit)) >> this->block_size_bit;
    unsigned int tagTmp = addr >> (this->index_bit + this->block_size_bit);
    if(cache_line[index].empty()){
        cache_line[index].push_back(0);
        (*pos_in_cache_line) = 0;
        return 0;
    }
    else{
        for(unsigned int i=0; i<cache_line[index].size(); i++){
            if((*(this->cache))[i * this->set_num + index].tag == tagTmp){
                deque<char> ::iterator pos = find_value(&(cache_line[index]), (char)i);
                char pop_out = *pos;
                cache_line[index].erase(pos);
                cache_line[index].push_back(pop_out);
                (*pos_in_cache_line) = pop_out;
                return 1;
            }
        }
        if(cache_line[index].size() < (this->cache_way)){
            char tmp = cache_line[index].size();
            cache_line[index].push_back(tmp);
            (*pos_in_cache_line) = tmp; 
            return 0;
        }
        else{
            char pop_out = cache_line[index].front();
            cache_line[index].pop_front();
            cache_line[index].push_back(pop_out);
            (*pos_in_cache_line) = pop_out;
            return 0;
        }
    }
    return 0;
}

unsigned int CacheManager::read(unsigned int addr){
    // TODO:: implement replacement policy and return value
    int index = (addr & (((1 << this->index_bit) - 1) << this->block_size_bit)) >> this->block_size_bit;
    unsigned int tagTmp = addr >> (this->index_bit + this->block_size_bit);
    int block_index = (addr >> 2) & ((1 << (this->block_size_bit - 2)) - 1);
    char way_num = 0xFF;
    bool hit_miss = check_cache(addr, &way_num);
    int tag_pos_in_table = way_num * this->set_num + index;
    if((unsigned int)way_num > this->cache_way)
        throw "index in cache line is wrong!!!";
    if(hit_miss){
        return (*(this->cache))[tag_pos_in_table][block_index];
    }
    else{
        unsigned int return_data;
        unsigned int read_addr = ((tagTmp << this->index_bit) | index) << this->block_size_bit;
        unsigned int write_back_addr = (((*(this->cache))[tag_pos_in_table].tag << this->index_bit) | index) << this->block_size_bit;
        int block_len = (*(this->cache))[tag_pos_in_table].len;
        if(this->dirty[tag_pos_in_table] == 1){
            for(int i=0; i<block_len; i++){
                this->memory->write(write_back_addr | (i*4), (*(this->cache))[tag_pos_in_table][i]);
            }
            this->dirty[tag_pos_in_table] = 0;
        }
        for(int i=0; i<block_len; i++){
            unsigned int data = this->memory->read(read_addr | (i*4));
            (*(this->cache))[tag_pos_in_table][i] = data;
            if(i == block_index)
                return_data = data;
        }

        (*(this->cache))[tag_pos_in_table].tag = tagTmp;
        (*(this->cache))[tag_pos_in_table][block_index] = return_data;
        return (*(this->cache))[tag_pos_in_table][block_index];
    }
}

void CacheManager::write(unsigned int addr, unsigned int value){
    // TODO:: write value to addr
    int index = (addr & (((1 << this->index_bit) - 1) << this->block_size_bit)) >> this->block_size_bit;
    unsigned int tagTmp = addr >> (this->index_bit + this->block_size_bit);
    int block_index = (addr >> 2) & ((1 << (this->block_size_bit - 2)) - 1);
    char way_num = 0xFF;
    bool hit_miss = check_cache(addr, &way_num);
    int tag_pos_in_table = way_num * this->set_num + index;
    if((unsigned int)way_num > this->cache_way)
        throw "index in cache line is wrong!!!";
    if(hit_miss){
        (*(this->cache))[tag_pos_in_table][block_index] = value;
        this->dirty[tag_pos_in_table] = 1;
    }
    else{
        int block_len = (*(this->cache))[tag_pos_in_table].len;
        unsigned int write_back_addr = (((*(this->cache))[tag_pos_in_table].tag << this->index_bit) | index) << this->block_size_bit;
        unsigned int read_addr = ((tagTmp << this->index_bit) | index) << this->block_size_bit;
        if(this->dirty[tag_pos_in_table] == 1){    
            for(int i=0; i<block_len; i++){
                this->memory->write(write_back_addr | (i*4), (*(this->cache))[tag_pos_in_table][i]);
            }
        }
        for(int i=0; i<block_len; i++){
            unsigned int data = this->memory->read(read_addr | (i*4));
            (*(this->cache))[tag_pos_in_table][i] = data;
        }

        (*(this->cache))[tag_pos_in_table].tag = tagTmp;
        (*(this->cache))[tag_pos_in_table][block_index] = value; 
        this->dirty[tag_pos_in_table] = 1;
    }
}

unsigned int CacheManager::get_tag_bits(){
    return tag_bits;
}