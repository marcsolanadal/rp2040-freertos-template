#include <hardware/flash.h>
#include <hardware/sync.h>
#include <stdio.h>

#include "Flash.h"

// Set the target offset to the last sector of flash
#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)

int first_empty_page = -1;

void
Flash_stats()
{
    printf("\n-------------------------------------------------------------\n");
    printf("FLASH_PAGE_SIZE = %d\n", FLASH_PAGE_SIZE);
    printf("FLASH_SECTOR_SIZE = %d\n", FLASH_SECTOR_SIZE);
    printf("FLASH_BLOCK_SIZE = %d\n", FLASH_BLOCK_SIZE);
    printf("PICO_FLASH_SIZE_BYTES = %d\n", PICO_FLASH_SIZE_BYTES);
    printf("XIP_BASE = %#010x\n", XIP_BASE);
}

int
Flash_write(int buffer[])
{
    int *p, page, addr;

    for (page = 0; page < FLASH_SECTOR_SIZE / FLASH_PAGE_SIZE; page++) {
        addr = XIP_BASE + FLASH_TARGET_OFFSET + (page * FLASH_PAGE_SIZE);
        p = (int*)addr;
        // 0xFFFFFFFF cast as an int is -1 so this is how we detect an empty
        // page
        if (*p == -1 && page < 0) {
            printf("First empty page is #%d", page);
            page = first_empty_page;
        }
    }

    if (first_empty_page < 0) {
        Flash_eraseSector();
        first_empty_page = 0;
    }

    uint32_t ints = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET +
                          (first_empty_page * FLASH_PAGE_SIZE),
                        (uint8_t*)buffer,
                        FLASH_PAGE_SIZE);
    restore_interrupts(ints);

    return first_empty_page * FLASH_PAGE_SIZE;
}

int
Flash_read(int page_offset)
{
    int addr = XIP_BASE + FLASH_TARGET_OFFSET + page_offset;
    return *((int*)addr); // Place an int pointer at our memory-mapped address
}

void
Flash_eraseSector()
{
    printf("Erasing last sector...\n");
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    restore_interrupts(ints);
}