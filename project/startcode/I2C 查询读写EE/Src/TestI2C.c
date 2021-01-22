#include "TestI2C.h"

#define	I2CREAD		1	//I2C������
#define	I2CWRITE	0	//I2Cд����

#define	STARTBIT	0	
#define	RESTARTBIT	1
#define	STOPBIT		2

#define DEVICE_EE256	0xA2	//FM24C256��������ַ
#define ADDRLEN_EE256	2		//FM24C256�����ݵ�ַ����Ϊ2�ֽ�

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

uint8_t I2C_Write_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t k, n, status;
	
	if(Len > 128) return 0xFF;//һ��������128�ֽ�
	
	for( k=0; k<3; k++ )//ÿ�����д3�� 
	{                                   	
		status = 0;
		if( Sendaddr( Device, Addr, AddrLen, I2CWRITE ) ) 
		{
		  status = 1; //д��ʧ��
		}
		else 
		{
			for( n=0; n<Len; n++ )
			{
				//����һ���ֽ�
				if( I2C_Send_Byte( Buf[n] ) ) 
				{
				  status = 1; 
				  break;
				} //д��ʧ��
			}
		}
		//����ֹͣλ
		if( I2C_Send_Bit( STOPBIT ) ) 
			status = 1;
		
		if( status == 0 ) 
		{
		  Wait_for_end(Device);
		  break;
		} //д��ȷ
	}
	
	return( status );
}


uint8_t I2C_Read_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t k, n, status;
	
	if(Len > 128) return 0xFF;//һ��������128�ֽ�
	
	for( k=0; k<3; k++ )//ÿ������3��
	{
		status = 0;
		if( Sendaddr( Device, Addr, AddrLen, I2CREAD ) )
      status = 1; //д��ʧ��
		else 
		{
			for( n=0; n<Len; n++ )
			{
				if( n < (Len-1) )
					LL_I2C_MasterMode_SetMasterRespond(I2C,LL_I2C_SSP_MASTER_RESPOND_ACK);
				else
					LL_I2C_MasterMode_SetMasterRespond(I2C,LL_I2C_SSP_MASTER_RESPOND_NACK);
				
				//����һ���ֽ�
				if( I2C_Receive_Byte( Buf+n ) ) 
        {
          status = 1; 
          break;
        } 
	
			}
		}
		//����ֹͣλ
		if( I2C_Send_Bit( STOPBIT ) ) 
      status = 1;	//ʧ��
		
		if( status == 0 ) break;//����ȷ
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
}

uint8_t Test_I2C(void)
{
	uint8_t Device = DEVICE_EE256;
	uint16_t Addr;
	uint8_t AddrLen = ADDRLEN_EE256;
	uint8_t Buf[2];
	uint8_t Len = 0;
	uint8_t Result = 0;
	
	uint8_t TestData[2] = {0xAA,0x55}; 
	
	Addr = 0;
	Len = 2;
	I2C_Init();
	
	memset(Buf, 0, 2);
	Result = I2C_Read_Bottom(Device, Addr, AddrLen, Buf, Len);//��ee����
	
	memset(Buf, 0x55, 2);
	memcpy(Buf, TestData, 2);
	Result = I2C_Write_Bottom(Device, Addr, AddrLen, Buf, Len);//дee����
	
	memset(Buf, 0, 2);
	Result = I2C_Read_Bottom(Device, Addr, AddrLen, Buf, Len);//��ee����
	
	return Result;
}
