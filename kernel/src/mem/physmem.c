#include "physmem.h"
#include <stddef.h>
#include <stdint.h>

// Internal bitmap and variables (to be implemented)

void physmem_init(struct limine_memmap_entry *memmap, size_t entry_count) {
    // TODO: Parse memory map and initialize bitmap
}

void *pmm_alloc_page(void) {
    // TODO: Find a free page in the bitmap and mark it used
    return NULL;
}

void pmm_free_page(void *page) {
    // TODO: Mark the page as free in the bitmap
} 