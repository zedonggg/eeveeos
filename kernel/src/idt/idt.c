#include <stdint.h>
#include "idt.h"
#include "../log/log.h"

interrupt_descriptor idt[256];

idtr idt_register;

extern char vector_0_handler[];

void set_idt_entry(void *handler, uint8_t index, uint8_t dpl, interrupt_descriptor* idt) {
    interrupt_descriptor* cur = &idt[index];
    uint64_t handler_addr = (uint64_t) handler;

    cur->offset_1 = handler_addr & 0xFFFF;
    cur->offset_2 = (handler_addr >> 16) & 0xFFFF;
    cur->offset_3 = handler_addr >> 32;

    cur->ist = 0;
    cur->selector = 0x28;
    cur->type_attributes = 0b1110 | ((dpl & 0b11) << 5) |(1 << 7);
}

void load_idt() {
    idt_register.base = (uint64_t) &idt;
    idt_register.bounds = sizeof(idt) - 1;
    asm volatile("lidt %0" :: "m"(idt_register));
}

void interrupt_dispatch(stack_frame* ptr) {
    switch(ptr->vector_number) {
        case 0:
            console_log("test");
            return;
        default:
            __asm__ volatile ("outb %0, %1" : : "a"((uint8_t)'b'), "Nd"(0xE9));
    }
}

void init_idt() {
    for (int i = 0; i < 256; i++) {
        void *handler = (void *)((uintptr_t)&vector_0_handler + i * 16);
        set_idt_entry(handler, i, 0, idt);
    }

    load_idt();
}
