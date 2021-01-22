#include "main.h"
#include "user_init.h"
#include "uart.h"

struct UARTOpStruct
{
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
    
	//FL_UART_DisableIT_TXBuffEmpty(UART0);
	//�����жϴ���
	if((ENABLE == FL_UART_IsEnabledIT_RXBuffFull(UART0))
		&&(SET == FL_UART_IsActiveFlag_RXBuffFull(UART0)))
	{
		//�ж�ת�����յ�������
		tmp08 = FL_UART_ReadRXBuff(UART0);//�����жϱ�־��ͨ����ȡrxreg�Ĵ������
		FL_UART_WriteTXBuff(UART0, tmp08);
	}
	
	//�����жϴ���
	if((ENABLE == FL_UART_IsEnabledIT_TXShiftBuffEmpty(UART0))
		&&(SET == FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0)))
	{
		//�����жϱ�־��ͨ��дtxreg�Ĵ��������txifд1���
		//����ָ�����ȵ�����
		if(UARTxOp.TxOpc < UARTxOp.TxLen)
		{
			FL_UART_WriteTXBuff(UART0, UARTxOp.TxBuf[UARTxOp.TxOpc]); //����һ������
			UARTxOp.TxOpc++;
		}
		FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);	//��������жϱ�־
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
			GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;         //�������
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
            UART_InitStruct.baudRate            = 115200;							        //������
	        UART_InitStruct.dataWidth           = FL_UART_DATA_WIDTH_8B;			      	//����λ��
	        UART_InitStruct.stopBits            = FL_UART_STOP_BIT_WIDTH_1B;				//ֹͣλ
	        UART_InitStruct.parity              = FL_UART_PARITY_EVEN;				        //��żУ��
	        UART_InitStruct.transferDirection   = FL_UART_DIRECTION_TX_RX;	                //����-����ʹ��
            
    FL_UART_Init(UART0, &UART_InitStruct);
    
    
            /*NVIC�ж�����*/
			NVIC_DisableIRQ(UART0_IRQn);
			NVIC_SetPriority(UART0_IRQn,2);//�ж����ȼ�����
			NVIC_EnableIRQ(UART0_IRQn);
	
}
 
void Test_Uart0(void)
{
    uint8_t TestTxData[11] = "TestUart-TX";
	//Uart0_Init();//��ʼ��uart����
		
    //�жϷ�������
	UARTxOp.TxBuf = TestTxData;
	UARTxOp.TxLen = 11;
	UARTxOp.TxOpc = 0 + 1;      
	 
	FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);
	FL_UART_EnableIT_TXShiftBuffEmpty(UART0);
	FL_UART_WriteTXBuff(UART0, UARTxOp.TxBuf[0]);
	DelayMs(50);//�����ʱ
	FL_UART_DisableIT_TXShiftBuffEmpty(UART0);  
	FL_UART_EnableIT_RXBuffFull(UART0);
}
