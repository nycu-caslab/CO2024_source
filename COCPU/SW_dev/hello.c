#include "cpu_lib.h"

int g_var = 0;


int printFib(int n) {
    static int a = 0, b = 1, nextTerm;
    static int idx = 1;
    
    if(n > 0)
    {    
        nextTerm = a + b;    
        a = b;    
        b = nextTerm;
        idx++;
        printf(" Fib %d: %d\n", idx,nextTerm);
        printFib(n-1);    
    }
}

int main()
{
    printf("\n\n");
    printf(" =======================================================\n");
    printf(" |:'######:::'#######:::'######::'########::'##::::'##:|\n");
    printf(" |'##... ##:'##.... ##:'##... ##: ##.... ##: ##:::: ##:|\n");
    printf(" | ##:::..:: ##:::: ##: ##:::..:: ##:::: ##: ##:::: ##:|\n");
    printf(" | ##::::::: ##:::: ##: ##::::::: ########:: ##:::: ##:|\n");
    printf(" | ##::::::: ##:::: ##: ##::::::: ##.....::: ##:::: ##:|\n");
    printf(" | ##::: ##: ##:::: ##: ##::: ##: ##:::::::: ##:::: ##:|\n");
    printf(" |. ######::. #######::. ######:: ##::::::::. #######::|\n");
    printf(" |:......::::.......::::......:::..::::::::::.......:::|\n");
    printf(" =======================================================\n");
    printf(" HELLO WORLD ! ver. 3\n");
    printf(" Greetings from the 2024 CO course riscv CPU :) \n");
    printf("\n");
    g_var += 4;
    printf(" global_var is now %d\n", g_var);
    printf(" CAS lab @ = %d\n", 600 + 10 + 9);
    printFib(7);
    printf(" +-----------------------------------------------------+\n");
    printf(" |                                Compiled on 2024/6/3 |\n");
    printf(" |        CCFLAGS: -march=rv32i -fno-builtin -nostdlib |\n");
    printf(" +-----------------------------------------------------+\n");
    printf("\n\n");
    return 0;
}
