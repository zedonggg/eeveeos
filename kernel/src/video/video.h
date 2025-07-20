#ifndef VIDEO_H
#define VIDEO_H
#include "../flanterm/flanterm.h"
#include "../flanterm/backends/fb.h"
#include "../limine.h"

extern struct flanterm_context *ft_ctx;

void init_video();

void kprintf(const char* str);

#endif
