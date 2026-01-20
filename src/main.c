#include <visual_firmware/gpio.h>

#include "tasks/task_1.h"

static void default_handler(void) {
    while (true) {
        __asm__ __volatile__ ("nop");
    }
}

static void reset_handler(void) {
    task_1_run();
}

static void pendsv_handler(void) {
    while (true) {
        __asm__ __volatile__ ("nop");
    }
}

static void systick_handler(void) {
    while (true) {
        __asm__ __volatile__ ("nop");
    }
}

__attribute__((aligned(128)))
__attribute__((section(".vector_table")))
__attribute__((used))
static const uintptr_t vector_table[] = {
    0x20082000,
    (uintptr_t)reset_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)pendsv_handler,
    (uintptr_t)systick_handler,

};

__attribute__((aligned(4)))
__attribute__((section(".image_def")))
__attribute__((used))
static const uint32_t image_def[] = {
    0xFFFFDED3,
    0x10210142,
    0x000001FF,
    0x00000000,
    0xAB123579,
};
