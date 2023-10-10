#ifndef KERNX_TERM_H
#define KERNX_TERM_H

#include "include/lib/flanterm/flanterm.h"
#include "include/lib/flanterm/fb.h"
#include "include/lib/string/str.h"
#include "limine.h"


void term_init(void);

void printf(const char *str);

void print(const char *str);

#endif //KERNX_TERM_H
