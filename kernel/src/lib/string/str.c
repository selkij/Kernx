#include "../../include/lib/string/str.h"

size_t strlen(char *str) {
    char *t;
    size_t i = 0;

    for (t = str; *t != '\0'; t++) {
        i++;
    }

    return i;
}
