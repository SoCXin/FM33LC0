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
	
   //��ʼ��uartx����
	
	//��ѯ��������
	for(i=0; i<3; i++)
	{
        FL_UART_WriteTXBuff(UART0, TestTxData[i]);		//����������д�뷢�ͼĴ���
		while(SET != FL_UART_IsActiveFlag_TXBuffEmpty(UART0));		//�ȴ��������
		
	}
		
}
