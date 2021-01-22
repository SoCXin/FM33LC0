#include "TestUart.h"
#include "user_init.h"
struct UARTOpStruct{
	uint8_t *TxBuf;	//��������ָ��
	uint8_t TxLen;	//���������ݳ���
	uint8_t TxOpc;	//�ѷ������ݳ���	
	uint8_t *RxBuf;	//��������ָ��
	uint8_t RxLen;	//���������ݳ���
	uint8_t RxOpc;	//�ѽ������ݳ���
};
struct UARTOpStruct UARTxOp;


void UART0_IRQHandler(void)
{
	uint8_t tmp08;
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ReceiveBuffFull(UART0))
		&&(SET == LL_UART_IsActiveFlag_RXBF(UART0)))
	{
		//�ж�ת�����յ�������
		tmp08 = LL_UART_ReceiveData(UART0);//�����жϱ�־��ͨ����ȡrxreg�Ĵ������
		LL_UART_TransmitData(UART0, tmp08);
	}
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ShiftBuffEmpty(UART0))
		&&(SET == LL_UART_IsActiveFlag_TXSE(UART0)))
	{
		//�����жϱ�־��ͨ��дtxreg�Ĵ��������txifд1���
		//����ָ�����ȵ�����
		if(UARTxOp.TxOpc < UARTxOp.TxLen)
		{
			LL_UART_TransmitData(UART0, UARTxOp.TxBuf[UARTxOp.TxOpc]); //����һ������
			UARTxOp.TxOpc++;
		}
		LL_UART_ClearFlag_TXSE(UART0);	//��������жϱ�־
	}
}
	

void UART1_IRQHandler(void)
{
	uint8_t tmp08;
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ReceiveBuffFull(UART1))
		&&(SET == LL_UART_IsActiveFlag_RXBF(UART1)))
	{
		//�ж�ת�����յ�������
		tmp08 = LL_UART_ReceiveData(UART1);//�����жϱ�־��ͨ����ȡrxreg�Ĵ������
		LL_UART_TransmitData(UART1, tmp08);
	}
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ShiftBuffEmpty(UART1))
		&&(SET == LL_UART_IsActiveFlag_TXSE(UART1)))
	{
		//�����жϱ�־��ͨ��дtxreg�Ĵ��������txifд1���
		//����ָ�����ȵ�����
		if(UARTxOp.TxOpc < UARTxOp.TxLen)
		{
			LL_UART_TransmitData(UART1, UARTxOp.TxBuf[UARTxOp.TxOpc]); //����һ������
			UARTxOp.TxOpc++;
		}
		LL_UART_ClearFlag_TXSE(UART1);	//��������жϱ�־
	}
}

void UART4_IRQHandler(void)
{
	uint8_t tmp08;
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ReceiveBuffFull(UART4))
		&&(SET == LL_UART_IsActiveFlag_RXBF(UART4)))
	{
		//�ж�ת�����յ�������
		tmp08 = LL_UART_ReceiveData(UART4);//�����жϱ�־��ͨ����ȡrxreg�Ĵ������
		LL_UART_TransmitData(UART4, tmp08);
	}
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ShiftBuffEmpty(UART4))
		&&(SET == LL_UART_IsActiveFlag_TXSE(UART4)))
	{
		//�����жϱ�־��ͨ��дtxreg�Ĵ��������txifд1���
		//����ָ�����ȵ�����
		if(UARTxOp.TxOpc < UARTxOp.TxLen)
		{
			LL_UART_TransmitData(UART4, UARTxOp.TxBuf[UARTxOp.TxOpc]); //����һ������
			UARTxOp.TxOpc++;
		}
		LL_UART_ClearFlag_TXSE(UART4);	//��������жϱ�־
	}
}


void UART5_IRQHandler(void)
{
	uint8_t tmp08;
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ReceiveBuffFull(UART5))
		&&(SET == LL_UART_IsActiveFlag_RXBF(UART5)))
	{
		//�ж�ת�����յ�������
		tmp08 = LL_UART_ReceiveData(UART5);//�����жϱ�־��ͨ����ȡrxreg�Ĵ������
		LL_UART_TransmitData(UART5, tmp08);
	}
	
	//�����жϴ���
	if((ENABLE == LL_UART_IsEnbaledIT_ShiftBuffEmpty(UART5))
		&&(SET == LL_UART_IsActiveFlag_TXSE(UART5)))
	{
		//�����жϱ�־��ͨ��дtxreg�Ĵ��������txifд1���
		//����ָ�����ȵ�����
		if(UARTxOp.TxOpc < UARTxOp.TxLen)
		{
			LL_UART_TransmitData(UART5, UARTxOp.TxBuf[UARTxOp.TxOpc]); //����һ������
			UARTxOp.TxOpc++;
		}
		LL_UART_ClearFlag_TXSE(UART5);	//��������жϱ�־
	}
}



void Uartx_Init(UART_Type* UARTx)
{
    
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    LL_UART_InitTypeDef UART_InitStruct = {0};    
    
	switch((uint32_t)UARTx)
	{
		case UART0_BASE:
			//PA13:UART0-RX   PA14:UART0-TX
			GPIO_InitStruct.Pin = LL_GPIO_PIN_13|LL_GPIO_PIN_14;
			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.Pull = DISABLE;
			GPIO_InitStruct.RemapPin = DISABLE;
			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
			//PA2:UART0-RX   PA3:UART0-TX
//			GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
//			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.Pull = DISABLE;
//			GPIO_InitStruct.RemapPin = DISABLE;
//			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
		
			UART_InitStruct.ClockSrc = LL_RCC_UART_OPERATION_CLOCK_SOURCE_APBCLK1;
			/*NVIC�ж�����*/
			NVIC_DisableIRQ(UART0_IRQn);
			NVIC_SetPriority(UART0_IRQn,2);//�ж����ȼ�����
			NVIC_EnableIRQ(UART0_IRQn);
			break;
		
		case UART1_BASE:
			//PB13:UART1-RX   PB14:UART1-TX
			GPIO_InitStruct.Pin = LL_GPIO_PIN_13|LL_GPIO_PIN_14;
			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.Pull = DISABLE;
			GPIO_InitStruct.RemapPin = DISABLE;			
			LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
			//PC2:UART1-RX   PC3:UART1-TX
//			GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
//			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.Pull = DISABLE;
//			GPIO_InitStruct.RemapPin = DISABLE;
//			LL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
				
			UART_InitStruct.ClockSrc = LL_RCC_UART_OPERATION_CLOCK_SOURCE_APBCLK1;
			/*NVIC�ж�����*/
			NVIC_DisableIRQ(UART1_IRQn);
			NVIC_SetPriority(UART1_IRQn,2);//�ж����ȼ�����
			NVIC_EnableIRQ(UART1_IRQn);
			break;
			
		case UART4_BASE:
			//PB2:UART4-RX   PB3:UART4-TX
			GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.Pull = DISABLE;
			GPIO_InitStruct.RemapPin = DISABLE;			
			LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
			//PA0:UART4-RX   PA1:UART4-TX
//			GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
//			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.Pull = DISABLE;
//			GPIO_InitStruct.RemapPin = DISABLE;
//			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
			/*NVIC�ж�����*/
			NVIC_DisableIRQ(UART4_IRQn);
			NVIC_SetPriority(UART4_IRQn,2);//�ж����ȼ�����
			NVIC_EnableIRQ(UART4_IRQn);
			break;
		
		case UART5_BASE:
			//PD0:UART5-RX   PD1:UART5-TX
			GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
			GPIO_InitStruct.Pull = DISABLE;
			GPIO_InitStruct.RemapPin = DISABLE;			
			LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		
			//PC4:UART5-RX   PC5:UART5-TX
//			GPIO_InitStruct.Pin = LL_GPIO_PIN_4|LL_GPIO_PIN_5;
//			GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
//			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//			GPIO_InitStruct.Pull = DISABLE;
//			GPIO_InitStruct.RemapPin = DISABLE;
//			LL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
			/*NVIC�ж�����*/
			NVIC_DisableIRQ(UART5_IRQn);
			NVIC_SetPriority(UART5_IRQn,2);//�ж����ȼ�����
			NVIC_EnableIRQ(UART5_IRQn);
			break;
				
		default:
			break;
    }
	UART_InitStruct.BaudRate = 115200;								//������
	UART_InitStruct.DataWidth = LL_UART_DATAWIDTH_8B;				//����λ��
	UART_InitStruct.StopBits = LL_UART_STOPBITS_1;					//ֹͣλ
	UART_InitStruct.Parity = LL_UART_PARITY_EVEN;					//��żУ��
	UART_InitStruct.TransferDirection = LL_UART_DIRECTION_TX_RX;	//����-����ʹ��
	UART_InitStruct.InfraredModulation = DISABLE;			        
	LL_UART_Init(UARTx, &UART_InitStruct);
}
void Test_Uartx(UART_Type* UARTx)
{
	
	uint8_t TestTxData[11] = "TestUart-TX";

	Uartx_Init(UARTx);//��ʼ��uart����
		
		//�жϷ�������
	UARTxOp.TxBuf = TestTxData;
	UARTxOp.TxLen = 11;
	UARTxOp.TxOpc = 0 + 1;
	
	LL_UART_ClearFlag_TXSE(UARTx);
	LL_UART_EnableIT_ShiftBuffEmpty(UARTx);
	LL_UART_TransmitData(UARTx, UARTxOp.TxBuf[0]);
	DelayMs(50);//�����ʱ
	LL_UART_DisableIT_ShiftBuffEmpty(UARTx);
	LL_UART_EnableIT_ReceiveBuffFull(UARTx);
	
}
