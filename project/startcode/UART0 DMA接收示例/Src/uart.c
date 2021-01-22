#include "main.h"
#include "user_init.h"
#include "uart.h"
uint8_t DMARxData[5];

//void Uart0_Init(void)
//{
//    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//    FL_UART_InitTypeDef UART_InitStruct = {0};  

// //PA13:UART0-RX   PA14:UART0-TX
//			GPIO_InitStruct.pin        = FL_GPIO_PIN_13;
//			GPIO_InitStruct.mode       = FL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;         //推挽输出
//			GPIO_InitStruct.pull       = ENABLE;
//			GPIO_InitStruct.remapPin   = DISABLE;
//		FL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//		
//				
//			UART_InitStruct.clockSrc            = FL_RCC_UART0_CLK_SOURCE_APB1CLK;
//            UART_InitStruct.baudRate            = 115200;							        //波特率
//	        UART_InitStruct.dataWidth           = FL_UART_DATA_WIDTH_8B;			      	//数据位数
//	        UART_InitStruct.stopBits            = FL_UART_STOP_BIT_WIDTH_1B;				//停止位
//	        UART_InitStruct.parity              = FL_UART_PARITY_EVEN;				        //奇偶校验
//	        UART_InitStruct.transferDirection   = FL_UART_DIRECTION_NONE;	                  //接收-发送使能
//	     FL_UART_Init(UART0, &UART_InitStruct);				

//}

//void Uart0DMA_Init(void)
//{

//  FL_DMA_InitTypeDef DMA_InitStruct={0};
//    
//      
//                DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION1;			
//				DMA_InitStruct.direction = FL_DMA_DIR_PERIPHERAL_TO_RAM;	
//				DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;	
//				DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
//				DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;		
//				DMA_InitStruct.circMode = DISABLE;
//			FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_1);
//  
//}

void Uart0DMA_Config(uint8_t *buffer,uint32_t length)
{
  FL_DMA_ConfigTypeDef DMA_ConfigStruct={0}; 


                DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;
                DMA_ConfigStruct.transmissionCount = length-1;
            FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct,FL_DMA_CHANNEL_1);


}


void TestDMA_Uart0(void)
{
    //Uart0_Init();
    //Uart0DMA_Init();
    
	Uart0DMA_Config(DMARxData,5);		
				
    FL_DMA_Enable(DMA);     
	FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1);
	FL_DMA_EnableChannel(DMA, FL_DMA_CHANNEL_1);
    
    FL_UART_EnableRX(UART0);


    while (!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1));
	FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1);
 
}
