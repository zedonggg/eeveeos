#ifndef PMM_H
#define PMM_H
#include <stddef.h>
#include <stdint.h>

// Limine memory map entry structure
struct limine_memmap_entry;

typedef struct free_list_t {
    uint64_t size;
    struct free_list_t *next;
} free_list_t;

void init_pmm();
void push_free_node(free_list_t *node);
void *pmm_alloc();
void pmm_free(void *page); 
void print_free_list();

#endif
