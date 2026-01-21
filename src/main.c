#include <stdint.h>

#include <visual_firmware/scheduler.h>

extern uint8_t data_start[];
extern uint8_t data_end[];
extern uint8_t data_load[];
extern uint8_t bss_start[];
extern uint8_t bss_end[];
extern uint8_t stack_top[];

static void default_handler(void) {
    while (true) {
        __asm__ __volatile__ ("wfi");
    }
}

static void reset_handler(void) {
    for (uint8_t *source = data_load, *destination = data_start; destination < data_end;) {
        *destination++ = *source++;
    }
    for (uint8_t *destination = bss_start; destination < bss_end;) {
        *destination++ = 0;
    }
    scheduler_start();
}

__attribute__((aligned(128)))
__attribute__((section(".vector_table")))
__attribute__((used))
static const uintptr_t vector_table[] = {
    (uintptr_t)stack_top,
    (uintptr_t)reset_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    0,
    0,
    0,
    0,
    (uintptr_t)default_handler,
    (uintptr_t)default_handler,
    0,
    (uintptr_t)scheduler_pendsv_handler,
    (uintptr_t)scheduler_systick_handler,

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
