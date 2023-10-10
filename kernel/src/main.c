#include "include/main.h"

void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void _start(void) {
    term_init();

    printf("Hello, World!");
    printf("Hiii");

    // We're done, just hang...
    hcf();
}