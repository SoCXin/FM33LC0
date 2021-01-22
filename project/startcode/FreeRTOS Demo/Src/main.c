#include "main.h"
#include "user_init.h"
#include "FreeRTOS.h"
#include "TaskSystem.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "gpio.h"
#include "uart.h"
/**
  ****************************************************************************************************
  * @file    main.c
  * @author  FMSH Application Team
  * @brief   Header file of  LL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2019] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under the Mulan PSL v1.
  * can use this software according to the terms and conditions of the Mulan PSL v1.
  * You may obtain a copy of Mulan PSL v1 at:
  * http://license.coscl.org.cn/MulanPSL
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
  * PURPOSE.
  * See the Mulan PSL v1 for more details.
  *
  ****************************************************************************************************
  */

#define TASK_LED_PRIORITY       (tskIDLE_PRIORITY + 1)
#define TASK_ADC_PRIORITY      (tskIDLE_PRIORITY + 1)
#define TASK_UART_PRIORITY      (tskIDLE_PRIORITY + 1)

uint8_t TestRxData[100];

QueueHandle_t  ADC_QueueHandle;   
QueueHandle_t dmaSemaphore;

void HardFault_Handler(void)
{
	printf("hardfault\n");
}

void LedTask(void *pvParameters)
{
    pvParameters = pvParameters;
    while (1)
    {
        vTaskDelay(1000);
        LED1_TOG;
    }
}

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();
    
    /* Configure the system clock */
    /* SHOULD BE KEPT!!! */
    MF_SystemClock_Config();
    /* user init */
    UserInit();
    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
	
    /* MF 初始化*/
    MF_Config_Init();
    /* UART5 DMA初始化 */
    UARTx_DMA(UART5, TestRxData,10); 
    /* GPIO 初始化 */    
    GPIO_Init();
    ADC_QueueHandle = xSemaphoreCreateCounting(10,0);
    dmaSemaphore = xSemaphoreCreateCounting(10,0);
    xTaskCreate(LedTask, "Led", configMINIMAL_STACK_SIZE, NULL, TASK_LED_PRIORITY, NULL);      
    xTaskCreate(AdcTask, "Adc", configMINIMAL_STACK_SIZE, NULL, TASK_ADC_PRIORITY, NULL);    
    xTaskCreate(UartTask, "Uart", configMINIMAL_STACK_SIZE, NULL, TASK_UART_PRIORITY, NULL);       
    
    vTaskStartScheduler();
    while(1)
    {     


    }

}

void vApplicationIdleHook(void)
{
    // TODO: 空闲任务
}




