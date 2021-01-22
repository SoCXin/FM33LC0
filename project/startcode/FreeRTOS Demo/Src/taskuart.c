#include "taskSystem.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"


extern  uint8_t TestRxData[100];
extern QueueHandle_t dmaSemaphore;
void UartTask(void *pvParameters)
{
  int i;
    while (1)
    {       
        // Transmit Debug
        UARTx_DMA_Rx(UART5, TestRxData);
        if (xSemaphoreTake(dmaSemaphore,portMAX_DELAY) == pdPASS)
        {
          
            for(i=0;i<10;i++)
            {
              PRINT("UART: %x\r\n", TestRxData[i]);
            }
            PRINT("\n");
        
        }
      
    }
}

void DMA_IRQCallBack(void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  
    xSemaphoreGiveFromISR(dmaSemaphore,&xHigherPriorityTaskWoken );
}

