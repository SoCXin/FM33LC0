#include "main.h"
#include "user_init.h"
#include "uart.h"
void Uart0_Init(void)
{
}
void Test_Uart0(void)
{
    uint8_t TestTxData[3] = {0x55,0x4A,0x01};
	uint8_t i;
	
   //初始化uartx配置
	
	//查询发送数组
	for(i=0; i<3; i++)
	{
        FL_UART_WriteTXBuff(UART0, TestTxData[i]);		//将发送数据写入发送寄存器
		while(SET != FL_UART_IsActiveFlag_TXBuffEmpty(UART0));		//等待发送完成
		
	}
		
}
