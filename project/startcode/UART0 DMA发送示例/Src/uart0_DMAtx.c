#include "main.h"
#include "user_init.h"
#include "uart0_DMAtx.h"

void Uart0DMA_Config(uint8_t *buffer,uint32_t length)
{
  FL_DMA_ConfigTypeDef DMA_ConfigStruct={0}; 


                DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;
                DMA_ConfigStruct.transmissionCount = length-1;
            FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct,FL_DMA_CHANNEL_2);

}

void TestDMA_Uart0(void)
{
    uint8_t TestTxData[11] = "TestUart-TX";
	volatile uint8_t tmp08;
	    
    FL_DMA_Enable(DMA);
    
	Uart0DMA_Config(TestTxData,11);
     
	FL_UART_EnableTX(UART0);

	while (!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_2));
	FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_2);
	FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);
	
    // 等待发送完成
    while (FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0) == RESET){};
    FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);	
	
}
