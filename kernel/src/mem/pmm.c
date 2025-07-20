#include "pmm.h"
#include "../utils/utils.h"
#include "../video/video.h"
#include "../log/log.h"
#include <stddef.h>
#include <stdint.h>
#include <limine.h>

free_list_t *head = NULL;

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request mm_req = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = LIMINE_API_REVISION,
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_hhdm_request hhdm_req = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = LIMINE_API_REVISION,
};

void push_free_node(free_list_t *node) {
    if (head == NULL) {
        head = node;
    } else {
        node->next = head;
        head = node;
    }
}

void print_free_list() {
    free_list_t *cur = head;
    kprintf("Available memory regions:\n");

    // while (cur != NULL) {
    //     kprintf("Address: ");
    //     kprintf((char *) cur + '\0');
    //     kprintf(" Size: ");
    //     kprintf((char *) cur->size + '\0');
    //     kprintf("\n");
    //     cur = cur->next;
    // }
}

void init_pmm() {
    kprintf("Initializing physical memory...");
    if (mm_req.response == NULL || hhdm_req.response == NULL) {
        kprintf("Error fetching memory map!");
        asm("hlt");
    }

    uint64_t offset = hhdm_req.response->offset;

    for (size_t i = 0; i < mm_req.response->entry_count; ++i) {
        struct limine_memmap_entry *entry = mm_req.response->entries[i];

        if (entry->type != LIMINE_MEMMAP_USABLE) {
            continue;
        }

        free_list_t *cur = (free_list_t *)(entry->base + offset);
        cur->size = entry->length;
        cur->next = NULL;
        push_free_node(cur);
    }

    print_free_list();
    kprintf("Physical memory initialized\n");
}

void *pmm_alloc(void) {
    return NULL;
}

void pmm_free(void *page) {

}
