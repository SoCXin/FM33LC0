#include "lpuart.h"
#include "main.h"
#include "user_init.h"

LPUARTOpTypeDef LPUARTOp;

uint8_t TestTxData[12] = {0x61,0x35,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12};

void LPUART0_IRQHandler(void)
{
	uint8_t temp;
	
	//�����жϴ���
	if((ENABLE == LL_LPUART_IsEnabledIT_RXBF(LPUART0))
		&&(SET == LL_LPUART_IsActiveFlag_RXBF(LPUART0)))//��������ƥ���ж�
	{
		temp = LL_LPUART_ReceiveData(LPUART0);   
	}
	
	//�����жϴ���
	if((ENABLE == LL_LPUART_IsEnabledIT_TXSE(LPUART0))
		&&(SET == LL_LPUART_IsActiveFlag_TXSE(LPUART0)))
	{
		//��������жϱ�־
    LL_LPUART_ClearFlag_TXSE(LPUART0);
    
    //����ָ�����ȵ�����
		if(LPUARTOp.TxOpc < LPUARTOp.TxLen)
		{
			LL_LPUART_TransmitData(LPUART0,LPUARTOp.TxBuf[LPUARTOp.TxOpc]); //����һ������
		}
	
    LPUARTOp.TxOpc++;
	}
}

void LPUART1_IRQHandler(void)
{
	uint8_t temp;
	
	//�����жϴ���
	if((ENABLE == LL_LPUART_IsEnabledIT_RXBF(LPUART1))
		&&(SET == LL_LPUART_IsActiveFlag_RXBF(LPUART1)))//��������ƥ���ж�
	{
		temp = LL_LPUART_ReceiveData(LPUART1);   
	}
	
	//�����жϴ���
	if((ENABLE == LL_LPUART_IsEnabledIT_TXSE(LPUART1))
		&&(SET == LL_LPUART_IsActiveFlag_TXSE(LPUART1)))
	{
		//����ָ�����ȵ�����
		if(LPUARTOp.TxOpc < LPUARTOp.TxLen)
		{
			LL_LPUART_TransmitData(LPUART1,LPUARTOp.TxBuf[LPUARTOp.TxOpc]); //����һ������
		}
		//��������жϱ�־
    LL_LPUART_ClearFlag_TXSE(LPUART1);
    LPUARTOp.TxOpc++;
	}
}

void LPUART_Init(LPUART_Type* LPUARTx)
{
    LL_LPUART_InitTypeDef  InitStructer;
    LL_GPIO_InitTypeDef  GPIO_InitStruct = {0};
    volatile uint8_t tmp08;
      
    if(LPUARTx==LPUART0)
    {
        GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;              //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;     //�������
        GPIO_InitStruct.Pull = ENABLE;                            //����ʹ������
        GPIO_InitStruct.RemapPin = ENABLE;                        //ʹ�ܶ������ֹ���
        LL_GPIO_Init(GPIOA,&GPIO_InitStruct);                     //PA13
        
        GPIO_InitStruct.Pin = LL_GPIO_PIN_14;                     
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;               //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;      //�������
        GPIO_InitStruct.Pull = DISABLE;                            //���Ͳ�����
        GPIO_InitStruct.RemapPin = ENABLE;                         //ʹ�ܶ������ֹ���    
        LL_GPIO_Init(GPIOA,&GPIO_InitStruct);                      //PA14
    }
    if(LPUARTx==LPUART1)
    {
        GPIO_InitStruct.Pin = LL_GPIO_PIN_13;                           
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;                //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;       //�������
        GPIO_InitStruct.Pull = ENABLE;                              //����ʹ������
        GPIO_InitStruct.RemapPin = ENABLE;                          //ʹ�ܶ������ֹ���  
        LL_GPIO_Init(GPIOB,&GPIO_InitStruct);                       //PB13
      
        GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;                //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;       //�������
        GPIO_InitStruct.Pull = DISABLE;                             //���Ͳ�����
        GPIO_InitStruct.RemapPin = ENABLE;                          //ʹ�ܶ������ֹ���  
        LL_GPIO_Init(GPIOB,&GPIO_InitStruct);                       //PB14
    }
    
    InitStructer.BaudRate            = LL_LPUART_BAUDRATE_9600;  //������9600
	  InitStructer.DataWidth           = LL_LPUART_DATAWIDTH_8B;   //8λ����λ
	  InitStructer.StopBits            = LL_LPUART_STOP_1BITS;     //1λֹͣλ
	  InitStructer.Parity              = LL_LPUART_PARITY_EVEN ;   //żУ��
	  InitStructer.TransferDirection   = LL_LPUART_DIRECTION_TX_RX;   //ʹ�ܷ��ͺͽ���
    LL_LPUART_Init(LPUARTx,&InitStructer);     
}

void LPUART_Test(LPUART_Type* LPUARTx)
{       
    if(LPUARTx==LPUART0)
    {
      NVIC_DisableIRQ(LPUART0_IRQn);
      NVIC_SetPriority(LPUART0_IRQn,2);//�ж����ȼ�����
      NVIC_EnableIRQ(LPUART0_IRQn);     //ʹ��NVIC
    }
    if(LPUARTx==LPUART1)
    {
      NVIC_DisableIRQ(LPUART1_IRQn);
      NVIC_SetPriority(LPUART1_IRQn,2);//�ж����ȼ�����
      NVIC_EnableIRQ(LPUART1_IRQn);     //ʹ��NVIC
    }
    
    LL_LPUART_SetDataRecvedWakeupMode(LPUARTx,LL_LPUART_WAKE_UP_AFTER_CHECK);//�����жϼ�У��
    
    LPUARTOp.TxBuf = TestTxData;    //��������
    LPUARTOp.TxLen = 12;            //���ͳ���
    LPUARTOp.TxOpc = 0 + 1;         //׼�����͵����
    
    LL_LPUART_ClearFlag_TXSE(LPUARTx);   //��������жϱ�־  
    LL_LPUART_EnabledIT_TXSE(LPUARTx);   //���ͼĴ���������λ�Ĵ������ж�ʹ��
    LL_LPUART_TransmitData(LPUARTx,LPUARTOp.TxBuf[0]); //������һ�����ݵķ���
    
    DelayMs(100);
    
    LL_LPUART_DisableIT_TXSE(LPUARTx);   //��ֹ�����ж�
    LL_LPUART_EnabledIT_RXBF(LPUARTx);   //ʹ�ܽ����ж�
}
