#ifndef VISUAL_FIRMWARE_SCHEDULER_H
#define VISUAL_FIRMWARE_SCHEDULER_H

void scheduler_start(void);

void scheduler_pendsv_handler(void);
void scheduler_systick_handler(void);

#endif
