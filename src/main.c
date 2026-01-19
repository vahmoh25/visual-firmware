#include <visual_firmware/gpio.h>

static void reset_handler(void) {
    gpio_set_pad_control(14, (gpio_pad_control_t){
        .slewfast = 0,
        .schmitt = 1,
        .pde = 1,
        .pue = 1,
        .driver = GPIO_DRIVE_2MA,
        .ie = 1,
        .od = 0,
        .iso = 0,
    });
    gpio_set_function(14, GPIO_FUNCTION_SIO);
    gpio_set_out(14);
    while (true) {
        for (uint32_t i = 0; i < 1000000; i++){
            __asm__ __volatile__ ("nop");
        }
        gpio_xor_oe(14);
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
