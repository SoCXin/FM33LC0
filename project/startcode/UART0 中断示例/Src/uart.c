#include "main.h"
#include "user_init.h"
#include "uart.h"

struct UARTOpStruct
{
	uint8_t *TxBuf;	//发送数据指针
	uint8_t TxLen;	//待发送数据长度
	uint8_t TxOpc;	//已发送数据长度	
	uint8_t *RxBuf;	//接收数据指针
	uint8_t RxLen;	//待接收数据长度
	uint8_t RxOpc;	//已接收数据长度
};
struct UARTOpStruct UARTxOp;

void UART0_IRQHandler(void)
{
	uint8_t tmp08;
    
	//FL_UART_DisableIT_TXBuffEmpty(UART0);
	//接收中断处理
	if((ENABLE == FL_UART_IsEnabledIT_RXBuffFull(UART0))
		&&(SET == FL_UART_IsActiveFlag_RXBuffFull(UART0)))
	{
		//中断转发接收到的数据
		tmp08 = FL_UART_ReadRXBuff(UART0);//接收中断标志可通过读取rxreg寄存器清除
		FL_UART_WriteTXBuff(UART0, tmp08);
	}
	
	//发送中断处理
	if((ENABLE == FL_UART_IsEnabledIT_TXShiftBuffEmpty(UART0))
		&&(SET == FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0)))
	{
		//发送中断标志可通过写txreg寄存器清除或txif写1清除
		//发送指定长度的数据
		if(UARTxOp.TxOpc < UARTxOp.TxLen)
		{
			FL_UART_WriteTXBuff(UART0, UARTxOp.TxBuf[UARTxOp.TxOpc]); //发送一个数据
			UARTxOp.TxOpc++;
		}
		FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);	//清除发送中断标志
	}
}

void Uart0_Init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    FL_UART_InitTypeDef UART_InitStruct = {0};   

    
            GPIO_InitStruct.pin           = FL_GPIO_PIN_11;
            GPIO_InitStruct.mode          = FL_GPIO_MODE_DIGITAL;
            GPIO_InitStruct.outputType    = FL_GPIO_OUTPUT_PUSHPULL;
            GPIO_InitStruct.pull          = DISABLE;
    
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_RCHF);

		
			//PA13:UART0-RX   PA14:UART0-TX
			GPIO_InitStruct.pin        = FL_GPIO_PIN_13|FL_GPIO_PIN_14;
			GPIO_InitStruct.mode       = FL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;         //推挽输出
			GPIO_InitStruct.pull       = ENABLE;
			GPIO_InitStruct.remapPin = DISABLE;
			FL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
			//PA2:UART0-RX   PA3:UART0-TX
//			GPIO_InitStruct.pin         = FL_GPIO_PIN_2|FL_GPIO_PIN_3;
//			GPIO_InitStruct.mode        = FL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.outputType  = FL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.pull        = DISABLE;
//			GPIO_InitStruct.remapPin    = DISABLE;
//			FL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
		
			UART_InitStruct.clockSrc            = FL_RCC_UART0_CLK_SOURCE_APB1CLK;
            UART_InitStruct.baudRate            = 115200;							        //波特率
	        UART_InitStruct.dataWidth           = FL_UART_DATA_WIDTH_8B;			      	//数据位数
	        UART_InitStruct.stopBits            = FL_UART_STOP_BIT_WIDTH_1B;				//停止位
	        UART_InitStruct.parity              = FL_UART_PARITY_EVEN;				        //奇偶校验
	        UART_InitStruct.transferDirection   = FL_UART_DIRECTION_TX_RX;	                //接收-发送使能
            
    FL_UART_Init(UART0, &UART_InitStruct);
    
    
            /*NVIC中断配置*/
			NVIC_DisableIRQ(UART0_IRQn);
			NVIC_SetPriority(UART0_IRQn,2);//中断优先级配置
			NVIC_EnableIRQ(UART0_IRQn);
	
}
 
void Test_Uart0(void)
{
    uint8_t TestTxData[11] = "TestUart-TX";
	//Uart0_Init();//初始化uart配置
		
    //中断发送数组
	UARTxOp.TxBuf = TestTxData;
	UARTxOp.TxLen = 11;
	UARTxOp.TxOpc = 0 + 1;      
	 
	FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);
	FL_UART_EnableIT_TXShiftBuffEmpty(UART0);
	FL_UART_WriteTXBuff(UART0, UARTxOp.TxBuf[0]);
	DelayMs(50);//软件延时
	FL_UART_DisableIT_TXShiftBuffEmpty(UART0);  
	FL_UART_EnableIT_RXBuffFull(UART0);
}
