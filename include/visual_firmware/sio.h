#ifndef VISUAL_FIRMWARE_SIO_H
#define VISUAL_FIRMWARE_SIO_H

#include "gpio.h"

static constexpr uint32_t SIO_BASE = 0xD0000000;

__attribute__((always_inline))
__attribute__((used))
static inline void sio_set_out(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x018) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void sio_clr_out(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x020) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void sio_xor_out(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x028) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void sio_set_oe(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x038) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void sio_clr_oe(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x040) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void sio_xor_oe(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x048) = 1 << pin;
}

#endif
