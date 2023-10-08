#include "include/main.h"

static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void _start(void) {
    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    //TODO: Check what pitch is in the request?
    for (size_t i = 0; i < 200; i++) {
        volatile uint32_t *fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }

    print("test");

    //TODO: Add gdb

    // We're done, just hang...
    hcf();
}