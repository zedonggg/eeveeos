#include <stdint.h>
#include "gdt.h"

gdt_segment gdt_table[7];
GDTR gdtr;


gdt_segment init_gdt_segment(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt_segment res;

    res.limit = limit & 0xFFFF;
    res.base_low = base & 0xFFFF;
    res.base_mid = (base >> 16) & 0xFF;
    res.base_high = (base >> 24) & 0xFF;
    res.access = access;
    res.flags = flags;

    return res;
}

void init_gdt() {
    gdt_table[0] = init_gdt_segment(0,0,0,0);

    //16-bit code and data
    gdt_table[1] = init_gdt_segment(0, 0xFFFF, 0x9A, 0);
    gdt_table[2] = init_gdt_segment(0, 0xFFFF, 0x93, 0);

    //32-bit code and data
    gdt_table[3] = init_gdt_segment(0, 0xFFFF, 0x9A, 0xCF);
    gdt_table[4] = init_gdt_segment(0, 0xFFFF, 0x93, 0xCF);

    //64-bit code and data
    gdt_table[5] = init_gdt_segment(0, 0xFFFF, 0x9B, 0xAF);
    gdt_table[6] = init_gdt_segment(0, 0xFFFF, 0x93, 0xAF);

    gdtr.offset = (uint64_t) &gdt_table[0];
    gdtr.size = sizeof(gdt_segment) * 7 - 1;

    load_gdt(&gdtr);

}

__attribute__((naked)) void load_gdt(GDTR *gdtr) {
    __asm__ volatile (
        // rdi contains the pointer to our GDTR structure.
        "lgdt (%%rdi)\n\t"           // Load GDTR from memory pointed to by rdi.
        // Set all data segment registers to 0x30 (i.e. entry 6: 6 << 3)
        "mov $0x30, %%ax\n\t"       
        "mov %%ax, %%ds\n\t"
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%fs\n\t"
        "mov %%ax, %%gs\n\t"
        "mov %%ax, %%ss\n\t"
        // Now perform a far return to reload CS.
        "pushq $0x28\n\t"           // Push the new code segment selector (entry 5: 5 << 3 = 0x28).
        "leaq 1f(%%rip), %%rax\n\t"  // Load the address of label 1 into rax.
        "pushq %%rax\n\t"           
        "lretq\n\t"                 // Far return pops new CS and RIP.
        "1:\n\t"
        "retq\n\t"
        :
        :
        : "rax", "memory"
    );
}
