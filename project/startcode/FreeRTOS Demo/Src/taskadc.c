#include "taskSystem.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"
#include "adc.h"

extern uint16_t ADCbuffer[3];



extern QueueHandle_t  ADC_QueueHandle;

void AdcTask(void *pvParameters)
{
    uint8_t i;
    pvParameters = pvParameters;    
    
    while (1)
    {   
        GetConvertSample(); 
       
        if (xSemaphoreGive(ADC_QueueHandle)  == pdPASS)
        {
          for(i=0;i<3;i++)
          {
            PRINT("CONVERT: %d\r\n", ADCbuffer[i]);
          }
          PRINT("\n");
        }
        vTaskDelay(1000);
    }
}
