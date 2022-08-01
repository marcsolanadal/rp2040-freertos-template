#ifndef FLASH_H
#define FLASH_H

void
Flash_stats();

int
Flash_write(int buffer[]);

int
Flash_read(int page_offset);

void
Flash_eraseSector();

#endif