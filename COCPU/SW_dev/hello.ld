/*  FROM THE OSDI LINKER SCRIPT
*
*      THE MEMORY LAYOUT 
*
* 0xFFF +-------------+ <- (The memory is 4KB)
*       |             | 
* 0xCA0 |-------------| <- Stack top is 0xCA0 (which is 0x10 alligned).
*       |    stack    | <- Stack grows down as you have learnt in class.
*       |      v      | 
*       |             | 
*       |             | 
*       |      ^      |
*       |    heap     | <- Doesn't work since there r no malloc stuffs in cpu_lib.
*       |-------------| 
*       |    bss      | <- Unintialized static data, filled with 0.
*       |-------------| 
*       |    data     | <- Initailized variable.
*       |-------------| 
*       |    text     | <- Instructions for cpu_lib and main().
*       |-------------| 
*       |  text.init  | <- Instrucitons for init() which loads sp for main().
* 0x000 +-------------+ <- PC starts w/ 0x0, YOUR CODE STARTS HERE :)
*
*
*   - 2024/3/19 : Memory layout diagram is updated, and BSS is 0x10 aligned.
*   - 2024/3/18 : BSS init to 0 to fix the uninitialized global variable bug.
*   - 2024/3/13 : OSDI linker script is ported for the COCPU.
*/

SECTIONS
{
    . = 0x0;
    .text.init       : { KEEP(*(.text.init)) }
    .text            : {   *(.text)   }
    .data            : {   *(.data)   }
    .bss (NOLOAD)    : {   *(.bss)    } 
    .rodata          : {   *(.rodata) }
}
