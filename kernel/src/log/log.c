#include <stdint.h>
#include "log.h"

void console_log(const char *s) {
    while (*s) {
        __asm__ volatile ("outb %0, %1" : : "a"((uint8_t) *s), "Nd"(0XE9));
        s++;
    }
}
