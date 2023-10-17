#include "include/cpu/gdt.h"

struct gdt_entry {
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct tss {
    uint16_t limit;
    uint16_t base_low0;
    uint8_t base_low1;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_mid;
    uint32_t base_high;
    uint64_t reserved;
} __attribute__((packed));

struct gdtr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct gdt {
    struct gdt_entry entries[11];
    struct tss tss;
} __attribute__ ((packed));

struct gdtr gdtr;
struct gdt gdt;

extern set_gdtr(struct gdtr *gdt);

void gdt_init(void) {

    // These segments are based of Lyre-OS
    
     // Null Segment
    gdt.entries[0].limit = 0;
    gdt.entries[0].base_low = 0;
    gdt.entries[0].base_mid = 0;
    gdt.entries[0].access = 0;
    gdt.entries[0].granularity = 0;
    gdt.entries[0].base_high = 0;

    // Kernel 16 Code Segment
    gdt.entries[1].limit = 0xFFFF;
    gdt.entries[1].base_low = 0;
    gdt.entries[1].base_mid = 0;
    gdt.entries[1].access = 0b10011010;
    gdt.entries[1].granularity = 0b00000000;
    gdt.entries[1].base_high = 0;

    // Kernel 16 Data Segment
    gdt.entries[2].limit = 0xFFFF;
    gdt.entries[2].base_low = 0;
    gdt.entries[2].base_mid = 0;
    gdt.entries[2].access = 0b10010010;
    gdt.entries[2].granularity = 0b00000000;
    gdt.entries[2].base_high = 0;

    // Kernel 32 Code Segment
    gdt.entries[3].limit = 0xFFFF;
    gdt.entries[3].base_low  = 0;
    gdt.entries[3].base_mid = 0;
    gdt.entries[3].access = 0b10011010;
    gdt.entries[3].granularity = 0b11001111;
    gdt.entries[3].base_high = 0;

    // Kernel 32 Data Segment
    gdt.entries[4].limit = 0xFFFF;
    gdt.entries[4].base_low  = 0;
    gdt.entries[4].base_mid = 0;
    gdt.entries[4].access = 0b10010010;
    gdt.entries[4].granularity = 0b11001111;
    gdt.entries[4].base_high = 0;

    // Kernel 64 Code Segment
    gdt.entries[5].limit = 0;
    gdt.entries[5].base_low = 0;
    gdt.entries[5].base_mid = 0;
    gdt.entries[5].access = 0b10011010;
    gdt.entries[5].granularity = 0b00100000;
    gdt.entries[5].base_high = 0;

    // Kernel 64 Data Segment
    gdt.entries[6].limit = 0;
    gdt.entries[6].base_low = 0;
    gdt.entries[6].base_mid = 0;
    gdt.entries[6].access = 0b10010010;
    gdt.entries[6].granularity = 0;
    gdt.entries[6].base_high = 0;

    // We don't need SYSENTER entries so we just put dummy ones instead
    gdt.entries[7] = gdt.entries[0];
    gdt.entries[8] = gdt.entries[0];

    // User 64 Code Segment
    gdt.entries[9].limit = 0;
    gdt.entries[9].base_low = 0;
    gdt.entries[9].base_mid = 0;
    gdt.entries[9].access = 0b11111010;
    gdt.entries[9].granularity = 0b00100000;
    gdt.entries[9].base_high = 0;

    // User 64 Data Segment
    gdt.entries[10].limit = 0;
    gdt.entries[10].base_low = 0;
    gdt.entries[10].base_mid = 0;
    gdt.entries[10].access = 0b11110010;
    gdt.entries[10].granularity = 0;
    gdt.entries[10].base_high = 0;

    gdt.tss.limit = 104;
    gdt.tss.base_low0 = 0;
    gdt.tss.base_low1 = 0;
    gdt.tss.access = 0b10001001;
    gdt.tss.granularity = 0;
    gdt.tss.base_mid = 0;
    gdt.tss.base_high = 0;
    gdt.tss.reserved = 0;

    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (uint64_t) &gdt;

    set_gdtr(&gdt);

    printf("GDT initialized");
}