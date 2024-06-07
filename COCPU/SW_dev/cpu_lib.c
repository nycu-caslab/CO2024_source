#include <stdarg.h>
#include "cpu_lib.h"


#ifdef DEBUG_SIM
    #define UART_STALL_NUM 2
#else
    #define UART_STALL_NUM 4000
#endif
// 4000 is for 20MHz cpu clock configuration.


extern int main(void);

volatile unsigned int __stack_top = 0x00000CA0;

volatile unsigned int * uart_addr     = (volatile unsigned int *)0xA0000000;
volatile unsigned int * sevseg_stat   = (volatile unsigned int *)0xB0000000;
volatile unsigned int * sevseg_lwtst0 = (volatile unsigned int *)0xBCafe427;
volatile unsigned int * sevseg_lwtst1 = (volatile unsigned int *)0xBeefDead;
volatile unsigned int * sevseg_lwtst2 = (volatile unsigned int *)0xB0EC6190;
volatile unsigned int * sevseg_lwtst3 = (volatile unsigned int *)0xBFFFFFFF;

// The boot() is a special function that will be identify by the linker script
// and will be place at the very first part.
__attribute__((section(".text.init"))) 
void init(void)
{
    // for self-checking
    *sevseg_lwtst0 = 0xbCafe427;
    *sevseg_lwtst1 = 0xBeefDead;
    *sevseg_lwtst2 = 0xb0EC6190;
    *sevseg_lwtst3 = 0xbFFFFFFF;

    __asm__ volatile("li  sp, 0");
    __asm__ volatile("lw  sp, %lo(__stack_top)(x0)");
    volatile int _main_ret = main();
    exit(_main_ret);
}


int putc(int c)
{
    if (c == '\n')
    {
        for (int i = 0; i < UART_STALL_NUM; i++)
        {
            __asm__ volatile ("NOP");
        }
        *uart_addr = (unsigned char) '\r';
    }
    for (int i = 0; i < UART_STALL_NUM; i++)
    {
        __asm__ volatile ("NOP");
    }
    *uart_addr = (unsigned char) c;
    return 0;
}


#pragma GCC push_options
// The default optimization flag set in Makefile is "-O2", 
// change the flag here to O0 to stop compiler from generating
// unwanted or unsupported instructions.

#pragma GCC optimize ("O2")
// "-O0" may brings stabilization to your CPU,
// in the cost of generating more instructions.

// The lame-looking code below is a tug-of-war with the compiler to stop it from generating
// "mul", "div" and other instructions that are not supported by the lab CPU,
int __putdNonDiv(int value)
{
    if (value == 0) 
    {
        putc('0');
        return 0;
    }
    if (value > 100000000) return 0;

    int pwr_ten_arr[10]; 
    pwr_ten_arr[0] = 1;         pwr_ten_arr[1] = 10;       
    pwr_ten_arr[2] = 100;       pwr_ten_arr[3] = 1000;      
    pwr_ten_arr[4] = 10000;     pwr_ten_arr[5] = 100000;  
    pwr_ten_arr[6] = 1000000;   pwr_ten_arr[7] = 10000000;  
    pwr_ten_arr[8] = 100000000; pwr_ten_arr[9] = 1000000000;

    int max_pwr_idx = 9;
    while (pwr_ten_arr[max_pwr_idx] > value) 
    {
        max_pwr_idx--;
    }
    for (int i = max_pwr_idx; i > 0; --i) 
    {
        
        int digit = 48;
        while (pwr_ten_arr[i] < value) 
        {
            value -= pwr_ten_arr[i];
            digit++;
        }
        if (pwr_ten_arr[i] == value)
        {
            value -= pwr_ten_arr[i];
            digit++;
        }
        if (digit != 48 || i <= max_pwr_idx) 
        {
            putc(digit);
        }
    }
    int digit = 48;
    if (value == 0)
    {
        putc(digit);
        return 0;
    }
    while (1 < value) 
    {
        value -= 1;
        digit++;
    }
    digit++;
    putc(digit);
    return 0;
}
#pragma GCC pop_options


int printf(char* fmt, ...) 
{
    va_list list;
    for (va_start(list, fmt); *fmt; fmt++) 
    {
        if (*fmt == '%') 
        {
            fmt++;
            if (*fmt == 'd')
            {
                __putdNonDiv(va_arg(list, int));
            }
        }
        else
        {
            putc(*fmt);
        }
    }
    
    va_end(list);
    return 0;
}


void exit(int status)
{
    printf("PROGRAM EXITED WITH CODE %d.\n", status);
    *sevseg_stat = 2;
    while (1)
    {
        __asm__ volatile ("NOP");
    }
}
