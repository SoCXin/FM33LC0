#include "uart.h"
#include "user_init.h"
#include "taskSystem.h"

#if 0
#pragma import(__use_no_semihosting)                          
struct __FILE 
{ 
    int handle; 
};
FILE __stdout;       

void _sys_exit(int x) 
{ 
    x = x;
} 

int fputc(int ch, FILE *f)
{
    UART0->TXBUF = ch;
    while (!(UART0->ISR & (0x1 << 0)));
    UART0->ISR |= (0x1 << 0);
    
    return ch;
}
#endif

void DebugInit(void)
{
#ifdef DEBUG_PRINT   
   Uartx_Init(UART0);//初始化uart配置
   FL_UART_EnableTX(UART0);
#endif
}


void DMA_IRQHandler(void)
{
  if(FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_4))
  {
    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_4);
    DMA_IRQCallBack();
  } 
}


void Uartx_Init(UART_Type* UARTx)
{
    
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    FL_UART_InitTypeDef UART_InitStruct = {0};    
    
	switch((uint32_t)UARTx)
	{
		case UART0_BASE:
			//PA13:UART0-RX   PA14:UART0-TX
			GPIO_InitStruct.pin = FL_GPIO_PIN_13|FL_GPIO_PIN_14;
			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.pull = DISABLE;
			GPIO_InitStruct.remapPin = DISABLE;
			FL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
//			//PA2:UART0-RX   PA3:UART0-TX
//			GPIO_InitStruct.pin = FL_GPIO_PIN_2|FL_GPIO_PIN_3;
//			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.pull = DISABLE;
//			GPIO_InitStruct.remapPin = DISABLE;
//			FL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
		
			UART_InitStruct.clockSrc = FL_RCC_UART1_CLK_SOURCE_APB1CLK;
   
			/*NVIC中断配置*/
			NVIC_DisableIRQ(UART0_IRQn);
			NVIC_SetPriority(UART0_IRQn,2);//中断优先级配置
			NVIC_EnableIRQ(UART0_IRQn);
			break;
		
		case UART1_BASE:
			//PB13:UART1-RX   PB14:UART1-TX
			GPIO_InitStruct.pin = FL_GPIO_PIN_13|FL_GPIO_PIN_14;
			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.pull = DISABLE;
			GPIO_InitStruct.remapPin = DISABLE;			
			FL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
			//PC2:UART1-RX   PC3:UART1-TX
//			GPIO_InitStruct.pin = FL_GPIO_PIN_2|FL_GPIO_PIN_3;
//			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.pull = DISABLE;
//			GPIO_InitStruct.remapPin = DISABLE;
//			FL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
				
			UART_InitStruct.clockSrc = FL_RCC_UART1_CLK_SOURCE_APB1CLK;
			/*NVIC中断配置*/
			NVIC_DisableIRQ(UART1_IRQn);
			NVIC_SetPriority(UART1_IRQn,2);//中断优先级配置
			NVIC_EnableIRQ(UART1_IRQn);
			break;
			
		case UART4_BASE:
			//PB2:UART4-RX   PB3:UART4-TX
			GPIO_InitStruct.pin = FL_GPIO_PIN_2|FL_GPIO_PIN_3;
			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.pull = DISABLE;
			GPIO_InitStruct.remapPin = DISABLE;			
			FL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
			//PA0:UART4-RX   PA1:UART4-TX
//			GPIO_InitStruct.pin = FL_GPIO_PIN_0|FL_GPIO_PIN_1;
//			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.pull = DISABLE;
//			GPIO_InitStruct.remapPin = DISABLE;
//			FL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
			/*NVIC中断配置*/
			NVIC_DisableIRQ(UART4_IRQn);
			NVIC_SetPriority(UART4_IRQn,2);//中断优先级配置
			NVIC_EnableIRQ(UART4_IRQn);
			break;
		
		case UART5_BASE:
			//PD0:UART5-RX   PD1:UART5-TX
			GPIO_InitStruct.pin = FL_GPIO_PIN_0|FL_GPIO_PIN_1;
			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.pull = DISABLE;
			GPIO_InitStruct.remapPin = DISABLE;			
			FL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		
			//PC4:UART5-RX   PC5:UART5-TX
//			GPIO_InitStruct.pin = FL_GPIO_PIN_4|FL_GPIO_PIN_5;
//			GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.pull = DISABLE;
//			GPIO_InitStruct.remapPin = DISABLE;
//			FL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
			/*NVIC中断配置*/
			NVIC_DisableIRQ(UART5_IRQn);
			NVIC_SetPriority(UART5_IRQn,2);//中断优先级配置
			NVIC_EnableIRQ(UART5_IRQn);
			break;
				
		default:
			break;
    }
	UART_InitStruct.baudRate = 115200;								//波特率
	UART_InitStruct.dataWidth = FL_UART_DATA_WIDTH_8B;				//数据位数
	UART_InitStruct.stopBits = FL_UART_STOP_BIT_WIDTH_1B;					//停止位
	UART_InitStruct.parity = FL_UART_PARITY_EVEN;					//奇偶校验
	UART_InitStruct.transferDirection = FL_UART_DIRECTION_NONE;	//接收-发送不使能		        
	FL_UART_Init(UARTx, &UART_InitStruct);
}

void UARTx_DMA(UART_Type* UARTx, uint8_t *buffer,uint32_t length)
{
    FL_DMA_InitTypeDef DMA_InitStruct={0};
	FL_DMA_ConfigTypeDef DMA_ConfigStruct={0};
	
    if(UARTx != UART5) return;
    
    Uartx_Init(UART5);//初始化uart配置
    
    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION6;			
    DMA_InitStruct.direction = FL_DMA_DIR_PERIPHERAL_TO_RAM;	
    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;	
    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;		
    DMA_InitStruct.circMode = DISABLE;
    FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_4);		

	DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;	
    DMA_ConfigStruct.transmissionCount = length - 1;
    FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_4);
		 /*NVIC中断配置*/
    NVIC_DisableIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn,2);//中断优先级配置
    NVIC_EnableIRQ(DMA_IRQn);
    
    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_4);
    
    FL_DMA_EnableIT_TransferComplete(DMA,FL_DMA_CHANNEL_4);	

}

void UARTx_DMA_Rx(UART_Type* UARTx, uint8_t *buffer)
{   
    if(UARTx != UART5) return;

    FL_DMA_WriteMemoryAddress(DMA,(uint32_t)buffer,FL_DMA_CHANNEL_4);
    FL_DMA_Enable(DMA);     
    FL_DMA_EnableChannel(DMA, FL_DMA_CHANNEL_4);

    FL_UART_EnableRX(UART5);
}

