#ifndef VISUAL_FIRMWARE_TASK_H
#define VISUAL_FIRMWARE_TASK_H

void task_start(void);

void task_pendsv_handler(void);
void task_systick_handler(void);

#endif
