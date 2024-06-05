#include <iostream>
#include <memory>
#include <string>
#include <getopt.h>

#include "Evaluator.h"
#include "Memory.h"
#include "Cache.h"


using namespace std;

int main(int argc, char *argv[]){
    int cache_size = 1024;
    std::string filepath = "testcase.txt";

    Evaluator evaluator(cache_size, filepath);
    evaluator.run();
}
