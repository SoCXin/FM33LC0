#include "TestI2C.h"
#include "user_init.h"
struct I2COpStruct{
	uint8_t *Buf;//����ָ��
	uint8_t Len;	//���ݳ���
	uint8_t Opc;	//�Ѳ������ݳ���
	uint8_t Opt; //��������
	uint8_t Ops; //����״̬ 
};
struct I2COpStruct I2COp;

#define	I2CREAD		1	//I2C������
#define	I2CWRITE	0	//I2Cд����

#define I2COPBUSY	1	//I2C�ж��շ�������
#define I2COPFINISH	0	//I2C�ж��շ����

#define	STARTBIT		0	
#define	RESTARTBIT	1
#define	STOPBIT			2

#define DEVICE_FM38025T     0x64	//FM38025T��������ַ
#define ADDRLEN_FM38025T	1		//FM38025T�����ݵ�ַ����Ϊ1�ֽ�


void I2C_IRQHandler(void)
{
	static uint8_t ACKFlag;
	
	if(SET == LL_I2C_MasterMode_IsActiveFlag_TransmitCompleted(I2C))
	{
		LL_I2C_MasterMode_ClearFlag_TransmitCompleted(I2C);//���жϱ�־
		if(I2COp.Opt == I2CWRITE)//���ʹ���
		{
			if(I2COp.Opc < I2COp.Len)//����û����
			{
				//����һ���ֽ�
				LL_I2C_MasterMode_WriteDataBuff(I2C,I2COp.Buf[I2COp.Opc]);//д���ͻ���Ĵ���
				I2COp.Opc++;
			}
			else
			{
				LL_I2C_MasterMode_DisableIT_TransmitCompleted(I2C);//�ر�I2C�ж�
				LL_I2C_MasterMode_Enable_I2C_Stop(I2C);//����ֹͣλ
				while(!LL_I2C_MasterMode_IsActiveFlag_Stop(I2C));
				I2COp.Ops = I2COPFINISH;//�������
			}
		}
	}
	
	if(SET == LL_I2C_MasterMode_IsActiveFlag_ReceiveCompleted(I2C))
	{
		LL_I2C_MasterMode_ClearFlag_ReceiveCompleted(I2C);
		if(ACKFlag==0)
		{
			if(I2COp.Opt == I2CREAD)//���մ���
			{
				
				I2COp.Buf[I2COp.Opc] = LL_I2C_MasterMode_ReadDataBuff(I2C);//�����ջ���
				I2COp.Opc++;

				if( I2COp.Opc < (I2COp.Len-1) )
				{	
					LL_I2C_MasterMode_SetMasterRespond(I2C,LL_I2C_SSP_MASTER_RESPOND_ACK);//���������ӻ��Ļ�ӦΪ0
					LL_I2C_MasterMode_EnableReceive(I2C);//�򿪽���ʹ��
				}
				else
				{
					LL_I2C_MasterMode_SetMasterRespond(I2C,LL_I2C_SSP_MASTER_RESPOND_NACK);	//���������ӻ��Ļ�ӦΪ1
					ACKFlag = 1;
					LL_I2C_MasterMode_EnableReceive(I2C);//�򿪽���ʹ��
				}
					
			}
		}
		else
		{
			ACKFlag = 0;
			I2COp.Buf[I2COp.Opc] = LL_I2C_MasterMode_ReadDataBuff(I2C);///�����ջ���
			LL_I2C_MasterMode_DisableIT_ReceiveCompleted(I2C);//�ر�I2C�ж�
			LL_I2C_MasterMode_Enable_I2C_Stop(I2C);//����ֹͣλ
			while(!LL_I2C_MasterMode_IsActiveFlag_Stop(I2C));
			I2COp.Ops = I2COPFINISH;//�������			
		}
	}
}

uint8_t I2C_Send_Bit(uint8_t BIT_def ) 
{
	
	switch(BIT_def)
	{
		case STARTBIT:
				LL_I2C_MasterMode_Enable_I2C_Start(I2C);
				while(!LL_I2C_MasterMode_IsActiveFlag_Start(I2C));
			break;
		
		case RESTARTBIT:
				LL_I2C_MasterMode_Enable_I2C_Rstart(I2C);
				while(!LL_I2C_MasterMode_IsActiveFlag_Start(I2C));		
			break;
		
		case STOPBIT:
				LL_I2C_MasterMode_Enable_I2C_Stop(I2C);
				while(!LL_I2C_MasterMode_IsActiveFlag_Stop(I2C));		
			break;
		
		default:
			break;
	}
		
	return 0; //ok

}

uint8_t I2C_Send_Byte( uint8_t x_byte ) 
{

	LL_I2C_MasterMode_WriteDataBuff(I2C,x_byte);
	
	while(!LL_I2C_MasterMode_IsActiveFlag_TransmitCompleted(I2C));
	LL_I2C_MasterMode_ClearFlag_TransmitCompleted(I2C);

	if(!LL_I2C_MasterMode_IsActiveFlag_Nack(I2C))
	{
		return 0;
	}
	else
	{
		LL_I2C_MasterMode_ClearFlag_Nack(I2C);
		return 1;
	}

}

uint8_t I2C_Receive_Byte( uint8_t *x_byte ) 
{

	//i2c en, rcen
	LL_I2C_MasterMode_EnableReceive(I2C);
  while(!LL_I2C_MasterMode_IsActiveFlag_ReceiveCompleted(I2C));
  LL_I2C_MasterMode_ClearFlag_ReceiveCompleted(I2C);
	*x_byte=LL_I2C_MasterMode_ReadDataBuff(I2C);
	return 0;
}

uint8_t Sendaddr( uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t Opt ) 
{
	uint8_t result, Devi_Addr;
	
	Devi_Addr = Device;


	//-------------- start bit -------------
	result = I2C_Send_Bit( STARTBIT );//������ʼλ
	if( result != 0 ) return 1; //failure.
	
	//-------------- disable read -------------
	LL_I2C_MasterMode_DisableReceive(I2C);
	//-------------- device addr -------------
	result = I2C_Send_Byte( Devi_Addr ); //����������ַ
	if( result != 0 ) return 2; //failure.

	//--------------- data addr --------------
	if(AddrLen == 2)
	{
		result = I2C_Send_Byte( Addr>>8 ); //�������ݵ�ַ��8λ
		if( result != 0 ) return 3; //failure.
	}
	result = I2C_Send_Byte( Addr>>0 ); //�������ݵ�ַ��8λ
	if( result != 0 ) return 3; //failure.

	if( Opt == I2CREAD ) //������
	{
		result = I2C_Send_Bit( RESTARTBIT ); //��������ʼλ
		if( result != 0 ) return 5; //failure.
		
		result = I2C_Send_Byte( Devi_Addr|1 ); //����������ַ,��ȡ
		if( result != 0 ) return 5; //failure.
	}
		
	return 0; //ok
}


uint8_t Wait_for_end( uint8_t Device )
{
	uint8_t result, Devi_Addr;

	Devi_Addr = Device;
	
	Do_DelayStart(); //��Ҫ5ms���ڲ�д����, ѭ��һ������ʱ��: 42��Delay()��
	{
		I2C_Send_Bit( STARTBIT );	//������ʼλ

		result = I2C_Send_Byte( Devi_Addr ); //����������ַ

		I2C_Send_Bit( STOPBIT ); //����ֹͣλ

		if( result == 0 ) return 0; //���õ�ַ�ɹ�, д���ڽ���
    
	}While_DelayMsEnd(5);

	return 1; //���õ�ַʧ��
}

uint8_t I2C_Write_Bottom_Int(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t status;
	
	if(Len > 128) return 0xFF;//һ��������128�ֽ�
	
	I2COp.Buf = Buf;//���ݻ�������ַ
	I2COp.Len = Len;//������/�������ݳ���
	I2COp.Opc = 0;//�ѷ���/�������ݳ���
	I2COp.Opt = I2CWRITE;//��/д����
	I2COp.Ops = I2COPBUSY;//����״̬
                         	
	status = 0;
	if( Sendaddr( Device, Addr, AddrLen, I2CWRITE ) ) status = 1; //д��ʧ��
	else 
	{
		LL_I2C_MasterMode_ClearFlag_TransmitCompleted(I2C);
		LL_I2C_MasterMode_EnabledIT_TransmitCompleted(I2C);;//����I2C�ж�
		//����һ���ֽ�
		LL_I2C_MasterMode_WriteDataBuff(I2C,I2COp.Buf[I2COp.Opc]);//д���ͻ���Ĵ���
		I2COp.Opc++;
	}	
	return( status );
}

uint8_t I2C_Read_Bottom_Int(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t status;
	
	if(Len > 128) return 0xFF;//һ��������128�ֽ�
	
	I2COp.Buf = Buf;//���ݻ�������ַ
	I2COp.Len = Len;//������/�������ݳ���
	I2COp.Opc = 0;//�ѷ���/�������ݳ���
	I2COp.Opt = I2CREAD;//��/д����
	I2COp.Ops = I2COPBUSY;//����״̬
	
	status = 0;
	if( Sendaddr( Device, Addr, AddrLen, I2CREAD ) ) status = 1; //д��ʧ��
	else 
	{
		LL_I2C_MasterMode_ClearFlag_ReceiveCompleted(I2C); //���жϱ�־
		LL_I2C_MasterMode_EnabledIT_ReceiveCompleted(I2C);//����I2C�ж�
		LL_I2C_MasterMode_EnableReceive(I2C);//�򿪽���ʹ��
	}

	return( status );
}


void I2C_Init(void)
{
	LL_I2C_MasterMode_InitTypeDef   IICInitStructer;    
	LL_GPIO_InitTypeDef    GPIO_InitStruct={0};
	
	GPIO_InitStruct.Pin = LL_GPIO_PIN_11|LL_GPIO_PIN_12;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = DISABLE;
	LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
	IICInitStructer.ClockSource = LL_RCC_I2C_OPERATION_CLOCK_SOURCE_APBCLK1;
	IICInitStructer.BaudRate = 100000;
	LL_I2C_MasterMode_Init(I2C,&IICInitStructer);	
	
	NVIC_DisableIRQ(I2C_IRQn);
	NVIC_SetPriority(I2C_IRQn,2);
	NVIC_EnableIRQ(I2C_IRQn);	
}

uint8_t Test_I2C(void)
{
	uint8_t Device = DEVICE_FM38025T;
	uint16_t Addr;
	uint8_t AddrLen = ADDRLEN_FM38025T;
	uint8_t Buf[64];
	uint8_t Len = 0;
	uint8_t Result = 0;
	
	uint8_t TestData[7] = {0x59, 0x59, 0x23, 0x10, 0x31, 0x08, 0x18}; 
	
	
	Addr = 0;
	Len = 7;
	I2C_Init();
	
	memset(Buf, 0, 64);
	Result = I2C_Read_Bottom_Int(Device, Addr, AddrLen, Buf, Len);//��ee����
	if(Result == 0)while(I2COp.Ops != I2COPFINISH);//�ȴ���ȡ���
	
	memset(Buf, 0xAA, 64);
	memcpy(Buf, TestData, Len);
	Result = I2C_Write_Bottom_Int(Device, Addr, AddrLen, Buf, Len);//дee����
	if(Result == 0)while(I2COp.Ops != I2COPFINISH);//�ȴ��������
	DelayMs(5);//�����ʱ,�ȴ�ee�ڲ�д���
	
	memset(Buf, 0, 64);
	Result = I2C_Read_Bottom_Int(Device, Addr, AddrLen, Buf, Len);//��ee����
	if(Result == 0)while(I2COp.Ops != I2COPFINISH);//�ȴ���ȡ���
	
	//IWDT_Clr();             //��ϵͳ���Ź�	
	return Result;
}


