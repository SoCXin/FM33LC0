#include "main.h"
#include "u7816.h"
#include "user_init.h"

void U7816_Init(void)
{
    LL_U7816_InitTypeDef   U7816_InitStruct;
    
    LL_GPIO_InitTypeDef    GPIO_InitStruct;
      
    GPIO_InitStruct.Pin = LL_GPIO_PIN_11|LL_GPIO_PIN_12;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = DISABLE;
    LL_GPIO_Init(GPIOC,&GPIO_InitStruct);    //PC11��PC12 ����Ϊ���ֹ���
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = DISABLE;
    LL_GPIO_Init(GPIOC,&GPIO_InitStruct);   //PC10����ΪGPIO������ܣ��������RST�ź�
  
    U7816_InitStruct.Baud                  = 372-1;                                    //372��ETU���ͨ�Ų�����
    U7816_InitStruct.BlockGuard            = DISABLE;                                //���պͷ���֮�䲻����BGT
    U7816_InitStruct.StrongPullUp          = ENABLE;                                 //ͨ��ǿ����ʹ��
    U7816_InitStruct.ErrorGuardTime        = LL_U7816_ERROR_GUARD_TIME_X1_ETU;       //ERROR SIGNAL��GUARDTIMEΪ1~1.5ETU
    U7816_InitStruct.ErrorSignalTime       = LL_U7816_ERROR_SIGNAL_WIDTH_X2_ETU;     //ERROR SIGNAL���Ϊ2ETU
    U7816_InitStruct.ExtraGuardTime        = 0;                                      //����ʱ����Ķ��Ᵽ��ʱ��Ϊ0
    U7816_InitStruct.OutputClockFreqence   = 4000000;                                 //U7816����ʱ��           
    U7816_InitStruct.RxAutoErrorSignal     = LL_U7816_AUTO_RESPOND_ERR_SIG_ENABLE;   //����������żУ�����ط�ERROR SIGNAL
    U7816_InitStruct.Parity                = LL_U7816_PARITY_EVEN;                   //żУ��
    U7816_InitStruct.TxAutoRetry           = LL_U7816_AUTO_RETRY_ENABLE;             //����������żУ������Զ��ط�
    U7816_InitStruct.RetryCnt              = LL_U7816_RETRY_CNT_X1;                  //�Զ��ط�����1��
    U7816_InitStruct.RxGuardTime           = LL_U7816_GUARD_TIME_RX_X2_ETU;          //����2��GUARD TIME
    U7816_InitStruct.TxGuardTime           = LL_U7816_GUARD_TIME_TX_X2_ETU;          //����2��GUARD TIME
    U7816_InitStruct.TransferOrder         = LL_U7816_BIT_ORDER_FIRST_LSB;           //�������
    LL_U7816_Init(U7816,&U7816_InitStruct);
    
    LL_U7816_EnableClkOutPut(U7816);
}

void Delay_Netu( unsigned char Num )	//Num*1etu
{
	DelayUs(93*Num);	//1etu=93us(4M),����1etu=186us(2M)
}

//��λ��Ӧ����ʱ��Ϊ400/f~40000/f��100us~10ms
//����ֵ: 1Ϊ�½���; 0Ϊ�ޱ仯
uint8_t Judge_Edge(void)
{
	uint32_t i;

	Delay_Netu(1);

	for( i=0x00; i<100; i++ ) 	//Լ10ms(4M),����20ms(2M)
	{
		if( SET == LL_U7816_IsActiveFlag_RxBusy(U7816) ) //���ڽ���
		{
			return 1;
		}
		Delay_Netu(1);
	}
		
	return 0;
}

//�ʱ��ӦΪ9600etu,ĿǰΪ9600etu,1etu=93us
uint8_t Get_7816_Char( unsigned char *Data )
{
	uint32_t i;	
	
	for( i=0x00; i<10000; i++ ) 	//Լ900ms(4M),����1800ms(2M)
	{
//		IWDT_Clr();
		Delay_Netu(1);
		if( SET == LL_U7816_IsActiveFlag_RxComplete(U7816) ) //RX_FLAG�Ѿ���λ
		{
			*Data = LL_U7816_ReadBuff(U7816);

			return 1; //�ɹ�
		}

		if( SET == LL_U7816_IsActiveFlag_Error(U7816) ) //ERROR_FLAG�Ѿ���λ
		{
		  LL_U7816_ClearFlag_TxParityError(U7816);
      LL_U7816_ClearFlag_RxParityError(U7816);
      LL_U7816_ClearFlag_RxFreamError(U7816);
      LL_U7816_ClearFlag_RxOverFlow(U7816);
			
			return 2; //error
		}
		
	}
	
	return 3;
}

uint8_t Snd_7816_Byte( unsigned char Data )
{
	uint32_t i;

	Delay_Netu(2);				//��ʱ1��etu,��֤���豸�ȶ�����

	LL_U7816_WriteBuff(U7816,Data);
	
	for( i=0x00; i<400; i++ ) 	//Լ39ms(4M),����78ms(2M)
	{
//		IWDT_Clr();
		Delay_Netu(1);
		if( SET == LL_U7816_IsActiveFlag_TxBuffEmpty(U7816) )	//TX_FLAG��λ
		{
			return 0; //�ɹ�
		}

		if( SET == LL_U7816_IsActiveFlag_Error(U7816) )	//ERROR_FLAG��λ
		{
		  LL_U7816_ClearFlag_TxParityError(U7816);
      LL_U7816_ClearFlag_RxParityError(U7816);
      LL_U7816_ClearFlag_RxFreamError(U7816);
      LL_U7816_ClearFlag_RxOverFlow(U7816);
			
			return 1; //error
		}
	}
	
	return 1;
}

//���㼤��&�临λ
//��⵽�������, RST�õ͵�ƽ, VCC�ϵ�, ��ʱһ��ʱ��, IO����Ϊ����̬, CLK���ʱ���ź�(T0ʱ��)
//��T0��40000~45000��CLK��, ��RST��Ϊ�ߵ�ƽ(T1ʱ��), ��T1���400~40000��CLK��, ��λӦ��Ӧ�ÿ�ʼ, 
//��IC���ĸ�λӦ��û���ڴ�ʱ����ڿ�ʼ, �ն˽������ͷ�ʱ��.���յ���λӦ��, ��������Э��淶, ����Ҫ�ȸ�λ
uint8_t ColdReset(void)
{
	uint8_t n, Result, Temp_ATR;	// T0, TD1, TD2;
	uint8_t CardRst8B[13]			;	//CARD��λ��Ϣ�к�13�ֽ�
	
	DelayMs(100);//��ʱ100ms
  
  LL_U7816_EnableTx(U7816);
	LL_U7816_EnableRx(U7816);
	LL_U7816_EnableClkOutPut(U7816);
	//----------------------------------------------------------------------------------------------
	Result = LL_U7816_ReadBuff(U7816); //RX������, �����rx_flag=1, ����ͨ����ȡRXBUF������˱�־.

	LL_U7816_ClearFlag_TxParityError(U7816);
  LL_U7816_ClearFlag_RxParityError(U7816);
  LL_U7816_ClearFlag_RxFreamError(U7816);
  LL_U7816_ClearFlag_RxOverFlow(U7816);

	LL_GPIO_ResetOutputPin(GPIOC,LL_GPIO_PIN_10);		//RST����͵�ƽ
	//RSTʱ�䱣����40000~45000��CLK;4MƵ����Ӧ�ñ��ֲ�����10ms;
	DelayMs(11);//�ȴ�RSTʱ��,����400����,��100us
	//-------- T1ʱ��, RST����ߵ�ƽ --------
	LL_GPIO_SetOutputPin(GPIOC,LL_GPIO_PIN_10);		
	//����λ��ɺ������������,֮ǰIO��ƽ���ȶ�,
  
	//��λ�����400~40000��CLK����ATR����
	Result = Judge_Edge(); 		//40000��CLK�ڲ鿴IO�ڵĵ�ƽ�ر仯
	if( Result == 0 ) //IO��û�г����½���
	{
		return 2;	//�쳣: 40000��CLK��û���յ���ʼλ
	}
	
	for(n=0; n<13; n++)
	{
		Result = Get_7816_Char(&Temp_ATR ); //receive TS.
		if( Result != 1 )
		{ 
			return 3; 
		}
		CardRst8B[ n ] = Temp_ATR;
	}
	
	if(CardRst8B[0] != 0x3b)
	{
		return 3; 
	}
	
	return 0;
}
