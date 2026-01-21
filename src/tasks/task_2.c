#include "task_1.h"

#include <visual_firmware/gpio.h>

void task_2_run(void) {
    gpio_set_pad_control(17, (gpio_pad_control_t){
        .slewfast = 0,
        .schmitt = 1,
        .pde = 1,
        .pue = 1,
        .driver = GPIO_DRIVE_2MA,
        .ie = 1,
        .od = 0,
        .iso = 0,
    });
    gpio_set_function(17, GPIO_FUNCTION_SIO);
    gpio_set_out(17);
    while (true) {
        for (uint32_t i = 0; i < 1000000; i++){
            __asm__ __volatile__ ("nop");
        }
        gpio_xor_oe(17);
    }
}
