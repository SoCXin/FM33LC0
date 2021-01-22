#include "main.h"
#include "user_init.h"
#include "uart0_rxtx.h"

void Test_Uart0(void)
{
    uint8_t TestTxData[3] = {0x55,0x4A,0x01};
	uint8_t i;
	volatile uint8_t tmp08;
	
   //��ʼ��uartx����
	
	//��ѯ��������
	for(i=0; i<3; i++)
	{
        FL_UART_WriteTXBuff(UART0, TestTxData[i]);		//����������д�뷢�ͼĴ���
		while(SET != FL_UART_IsActiveFlag_TXBuffEmpty(UART0));		//�ȴ��������
		
	}
	
	//ת�����յ�������
	while(1)
	{
		if(SET == FL_UART_IsActiveFlag_RXBuffFull(UART0))		//�ȴ����յ�һ���ֽ�
		{
			tmp08 = FL_UART_ReadRXBuff(UART0);					//uart�����жϱ�־��ͨ����ȡrxreg���
			FL_UART_WriteTXBuff(UART0, tmp08);			//���յ������ݷ��ͻ�ȥ
		}
	}

}
