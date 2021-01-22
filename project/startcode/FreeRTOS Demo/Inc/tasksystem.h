#ifndef __TASKSYSTEM_H__
#define __TASKSYSTEM_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void AdcTask(void *pvParameters);
void UartTask(void *pvParameters);
void DMA_IRQCallBack(void);
#endif
