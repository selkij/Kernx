#ifndef KERNX_MAIN_H
#define KERNX_MAIN_H

#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "term.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0
};

#endif //KERNX_MAIN_H
