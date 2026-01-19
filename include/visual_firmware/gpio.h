#ifndef VISUAL_FIRMWARE_GPIO_H
#define VISUAL_FIRMWARE_GPIO_H

#include <stdint.h>

static constexpr uint32_t IO_BANK0_BASE = 0x40028000;
static constexpr uint32_t PADS_BANK0_BASE = 0x40038000;
static constexpr uint32_t SIO_BASE = 0xD0000000;

typedef uint8_t gpio_pin_t;

typedef enum : uint8_t {
    GPIO_DRIVE_2MA = 0,
    GPIO_DRIVE_4MA = 1,
    GPIO_DRIVE_8MA = 2,
    GPIO_DRIVE_12MA = 3,
} gpio_drive_t;

typedef enum : uint8_t {
    GPIO_FUNCTION_SIO = 5,
} gpio_function_t;

typedef union {
    struct {
        uint32_t slewfast : 1;
        uint32_t schmitt : 1;
        uint32_t pde : 1;
        uint32_t pue : 1;
        uint32_t driver : 2;
        uint32_t ie : 1;
        uint32_t od : 1;
        uint32_t iso : 1;
        uint32_t reserved : 23;
    };
    uint32_t raw;
} gpio_pad_control_t;

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_set_pad_control(gpio_pin_t pin, gpio_pad_control_t pad_control) {
    *(volatile uint32_t *)(PADS_BANK0_BASE + 0x04 + (pin * 4)) = pad_control.raw;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_set_function(gpio_pin_t pin, gpio_function_t function) {
    *(volatile uint32_t *)(IO_BANK0_BASE + 0x04 + (pin * 8)) = function;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_set_out(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x018) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_clr_out(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x020) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_xor_out(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x028) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_set_oe(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x038) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_clr_oe(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x040) = 1 << pin;
}

__attribute__((always_inline))
__attribute__((used))
static inline void gpio_xor_oe(gpio_pin_t pin) {
    *(volatile uint32_t *)(SIO_BASE + 0x048) = 1 << pin;
}

#endif
