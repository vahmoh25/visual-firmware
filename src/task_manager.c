#include <visual_firmware/task.h>

#include <stdint.h>

#include "tasks/task_1.h"
#include "tasks/task_2.h"
#include "tasks/task_3.h"

#define TASKS \
    X(task_1_run) \
    X(task_2_run) \
    X(task_3_run) \

constexpr uint32_t TASK_STACK_SIZE = 128;

#define X(name) static uint32_t name##_stack[TASK_STACK_SIZE];
TASKS
#undef X

typedef struct {
    void (*entry)(void);
    uint32_t *stack_base;
    uint32_t *stack_top;
} task_t;

#define X(name) { name, name##_stack, nullptr },
static task_t tasks[] = {
    TASKS
};
#undef X

#define X(name) + 1
constexpr uint8_t TASK_NUMBER = 0 TASKS;
#undef X

constexpr uint32_t SYST_CSR = 0xE000E010;
constexpr uint32_t SYST_RVR = 0xE000E014;
constexpr uint32_t SYST_CVR = 0xE000E018;

constexpr uint32_t SCB_ICSR = 0xE000ED04;
constexpr uint32_t SCB_SHPR3 = 0xE000ED20;

static uint8_t current_task;

uint32_t *schedule_next_task(uint32_t *current_sp) {
    tasks[current_task].stack_top = current_sp;
    current_task = (current_task + 1) % TASK_NUMBER;
    return tasks[current_task].stack_top;
}

void task_start(void) {
    for (uint8_t i = 0; i < TASK_NUMBER; i++) {
        tasks[i].stack_top = tasks[i].stack_base + TASK_STACK_SIZE;
        *(--tasks[i].stack_top) = 1 << 24;
        *(--tasks[i].stack_top) = (uint32_t)tasks[i].entry;
        for (uint8_t j = 0; j < 14; j++) {
            *(--tasks[i].stack_top) = 0;
        }
    }
    (*(volatile uint32_t *)SCB_SHPR3) = 0xFF << 16;
    (*(volatile uint32_t *)SYST_RVR) = 100000;
    (*(volatile uint32_t *)SYST_CVR) = 0;
    (*(volatile uint32_t *)SYST_CSR) = (1 << 0) | (1 << 1) | (1 << 2);
    __asm volatile (
        "add r0, %0, #64 \n"
        "msr psp, r0 \n"
        "mov r0, #2 \n"
        "msr control, r0 \n"
        "ldr pc, [%0, #56] \n"
        :: "r" (tasks[0].stack_top)
        : "r0"
    );
}

__attribute__((naked))
void task_pendsv_handler(void) {
    __asm volatile (
        "mrs r0, psp \n"
        "stmdb r0!, {r4-r11} \n"
        "bl schedule_next_task \n"
        "ldmia r0!, {r4-r11} \n"
        "msr psp, r0 \n"
        "ldr r0, =0xFFFFFFFD \n"
        "bx r0 \n"
    );
}

void task_systick_handler(void) {
    *(volatile uint32_t *)(SCB_ICSR) = 1 << 28;
}
