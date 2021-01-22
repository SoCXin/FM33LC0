#include "main.h"
#include "user_init.h"
#include "uart0_DMArx.h"
uint8_t DMARxData[5];

void Uart0DMA_Config(uint8_t *buffer,uint32_t length)
{
  FL_DMA_ConfigTypeDef DMA_ConfigStruct={0}; 


                DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;
                DMA_ConfigStruct.transmissionCount = length-1;
            FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct,FL_DMA_CHANNEL_1);


}

void TestDMA_Uart0(void)
{
    FL_DMA_Enable(DMA); 
    
	Uart0DMA_Config(DMARxData,5);		
				   
    FL_UART_EnableRX(UART0);

    while (!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1));
	FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1);
 
}
