#ifndef IDT_H
#define IDT_H
#include <stdint.h>

typedef struct {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t reserved;            // reserved
} __attribute__((packed)) interrupt_descriptor;

typedef struct {
	uint16_t bounds;
	uint64_t base;
} __attribute__((packed)) idtr;


typedef struct {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcs;
    uint64_t rbx;
    uint64_t rax;

    uint64_t vector_number;
    uint64_t error_code;

    uint64_t iret_rip;
    uint64_t iret_cs;
    uint64_t iret_flags;
    uint64_t iret_rsp;
    uint64_t iret_ss;
} __attribute__((packed)) stack_frame;

//extern interrupt_descriptor idt[256];

void set_idt_entry(void *handler, uint8_t index, uint8_t dpl, interrupt_descriptor* idt);

void load_idt();

void interrupt_dispatch(stack_frame *ptr);

void init_idt();


#endif
