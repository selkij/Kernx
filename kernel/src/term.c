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

    lprint(1, "Terminal initialized");
}

void print(const char *str) {
    if (ft_ctx != NULL) {
        flanterm_write(ft_ctx, str, strlen(str));
    }
}

void printf(const char *str) {
    print(str);
    print("\n");
}

void lprint(uint8_t level, const char *str) { 

    /*
    * Levels:
    * 0 - Info
    * 1 - Success
    * 2 - Warning
    * 3 - Error
    * 4 - Fatal
    */

    char* level_prefixes[5] = { LOG_INFO_PREFIX, LOG_SUCCESS_PREFIX, LOG_WARN_PREFIX, LOG_ERROR_PREFIX, LOG_FATAL_PREFIX };
    char* level_prefixes_compact[5] = { LOG_INFO_PREFIX_COMPACT, LOG_SUCCESS_PREFIX_COMPACT, LOG_WARN_PREFIX_COMPACT, LOG_ERROR_PREFIX_COMPACT, LOG_FATAL_PREFIX_COMPACT };
    if(LOG_COMPACT_MODE == 1) {
        print(level_prefixes_compact[level]);
    } else {
        print(level_prefixes[level]);
    }

    printf(str);
}

void lprint_test_level(void) {
    lprint(0, "This is a test");
    lprint(1, "This is a test");
    lprint(2, "This is a test");
    lprint(3, "This is a test");
    lprint(4, "This is a test");
}