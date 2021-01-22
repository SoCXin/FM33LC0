#ifndef __LPUART_H__
#define __LPUART_H__
#include "main.h"

typedef struct 
{
	uint8_t *TxBuf;	//��������ָ��
	uint8_t TxLen;	//���������ݳ���
	uint8_t TxOpc;	//�ѷ������ݳ���
	uint8_t *RxBuf;	//��������ָ��
	uint8_t RxLen;	//���������ݳ���
	uint8_t RxOpc;	//�ѽ������ݳ���
}LPUARTOpTypeDef;

void LPUART_Init(LPUART_Type* LPUARTx);
void LPUART_Test(LPUART_Type* LPUARTx);

#endif

