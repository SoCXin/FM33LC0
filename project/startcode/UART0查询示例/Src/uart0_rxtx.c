#include "main.h"
#include "user_init.h"
#include "uart0_rxtx.h"

void Test_Uart0(void)
{
    uint8_t TestTxData[3] = {0x55,0x4A,0x01};
	uint8_t i;
	volatile uint8_t tmp08;
	
   //初始化uartx配置
	
	//查询发送数组
	for(i=0; i<3; i++)
	{
        FL_UART_WriteTXBuff(UART0, TestTxData[i]);		//将发送数据写入发送寄存器
		while(SET != FL_UART_IsActiveFlag_TXBuffEmpty(UART0));		//等待发送完成
		
	}
	
	//转发接收到的数据
	while(1)
	{
		if(SET == FL_UART_IsActiveFlag_RXBuffFull(UART0))		//等待接收到一个字节
		{
			tmp08 = FL_UART_ReadRXBuff(UART0);					//uart接收中断标志可通过读取rxreg清除
			FL_UART_WriteTXBuff(UART0, tmp08);			//将收到的数据发送回去
		}
	}

}
