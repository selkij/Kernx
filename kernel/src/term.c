#include "include/term.h"

volatile struct limine_framebuffer_request framebuffer_request = {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0
};

static struct flanterm_context *ft_ctx = NULL;

void term_init(void) {
    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
        asm ("cli");
        for (;;) {
            asm ("hlt");
        }
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    ft_ctx = flanterm_fb_simple_init(
            framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch
    );
}

void print(const char *str) {
    if (ft_ctx != NULL) {
        flanterm_write(ft_ctx, str, strlen(str));
    }
}

void printf(const char *str) {
    print(str);
    print('\n');
}