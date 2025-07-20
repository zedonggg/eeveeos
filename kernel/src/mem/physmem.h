#pragma once
#include <stddef.h>
#include <stdint.h>

// Limine memory map entry structure
struct limine_memmap_entry;

void physmem_init(struct limine_memmap_entry *memmap, size_t entry_count);
void *pmm_alloc_page(void);
void pmm_free_page(void *page); 