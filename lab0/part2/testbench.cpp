#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Valu.h"
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <time.h>
using namespace std;

Valu *top = new Valu;
vluint64_t sim_time = 0;
VerilatedVcdC *m_trace = new VerilatedVcdC;

typedef struct{
   unsigned int A : 4;
   unsigned int B : 4;
   unsigned int C : 4;
   unsigned int Y : 4;
}ABC;


void test(){
    ABC abc;
    for(int i=0; i<1000; i++){
        abc.A = rand() & 0xf;
        abc.B = rand() & 0xf;
        top->a = abc.A;
        top->b = abc.B;
        top->s = rand() & 0x7;
        int x = top->s;
        
        // generate golden answer
        switch(top->s) { 
            case 0:
                abc.C = abc.A + abc.B;
                break;
            case 1:
                abc.C = abc.A - abc.B;
                break;
            case 2:
                abc.C = ~abc.A;
                break;
            case 3:
                abc.C = abc.A & abc.B;
                break;
            case 4:
                abc.C = abc.A | abc.B;
                break;
            case 5:
                abc.C = abc.A ^ abc.B;
                break;
            case 6:
                abc.C = abc.A > abc.B ? 1 : 0;
                break;
            case 7:
                abc.C = abc.A == abc.B ? 1 : 0;
                break;
            default:
                abc.C = 0;
                break;
        }

        top->eval();
        m_trace->dump(sim_time);
        sim_time++;
        abc.Y = top->y;
        assert(abc.Y == abc.C);
        // cout<<top->ADD->a<<endl;
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
