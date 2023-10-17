#include "include/main.h"

void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void _start(void) {
    term_init();
    printf("a");
    gdt_init();

    printf("Kernx");
    
    // We're done, just hang...
    hcf();
}