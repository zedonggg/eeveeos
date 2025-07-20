#include <stdint.h>
#include "utils.h"
#include "../flanterm/flanterm.h"

int strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
