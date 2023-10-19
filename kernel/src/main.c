#include "include/main.h"

void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void _start(void) {
    term_init();
    gdt_init();

    lprint(2, "Kernx");
    
    // We're done, just hang...
    hcf();
}