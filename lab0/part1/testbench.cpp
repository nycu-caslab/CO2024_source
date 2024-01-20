#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VfullAdder.h"
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <time.h>
using namespace std;

VfullAdder *top = new VfullAdder;
vluint64_t sim_time = 0;
VerilatedVcdC *m_trace = new VerilatedVcdC;

void test(){
    for(int i=0; i<8; i++){
        int input[3] = {0};
        int tmp = i;
        for (int i = 2; i >= 0; i--){
            input[i] = tmp % 2;
            tmp /= 2;
        }

        top->cin = input[2];
        top->b = input[1];
        top->a = input[0];

        top->eval();
        m_trace->dump(sim_time);
        sim_time++;
        
        int ans = (top->a + top->b + top->cin);

        assert(top->cout == ans / 2);
        assert(top->s == ans % 2);
    }
    cout<<endl;
    cout<<"============================"<<endl;
    cout<<"\e[32m\e[1mPASS\e[0m\n";
}

int main() {
    time_t start, end;
    srand(1111);
    Verilated::traceEverOn(true);
    top->trace(m_trace, 99);
    m_trace->open("waveform.vcd");
    start = clock();
    test();   
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    m_trace->close();
    cout<<"cpu_time_used : "<<cpu_time_used<<endl;
    cout<<"============================"<<endl;
    delete top;
    return 0;
}
