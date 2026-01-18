#include <stdint.h>

static constexpr uint32_t IO_BANK0_BASE = 0x40028000;
static constexpr uint32_t PADS_BANK0_BASE = 0x40038000;
static constexpr uint32_t SIO_BASE = 0xD0000000;

static void reset_handler(void) {
    *(volatile uint32_t *)(IO_BANK0_BASE + 0x04 + (14 * 8)) = 5;
    *(volatile uint32_t *)(PADS_BANK0_BASE + 0x04 + (14 * 4)) &= ~(1 << 8);
    *(volatile uint32_t *)(SIO_BASE + 0x018) = (1 << 14);
    *(volatile uint32_t *)(SIO_BASE + 0x038) = (1 << 14);
    while (true) {
        __asm volatile ("wfi");
    }
}

__attribute__((aligned(128)))
__attribute__((section(".vector_table")))
__attribute__((used))
static const uintptr_t vector_table[2] = {
    0x20082000,
    (uintptr_t)reset_handler,
};

__attribute__((aligned(4)))
__attribute__((section(".image_def")))
__attribute__((used))
static const uint32_t image_def[5] = {
    0xFFFFDED3,
    0x10210142,
    0x000001FF,
    0x00000000,
    0xAB123579,
};
