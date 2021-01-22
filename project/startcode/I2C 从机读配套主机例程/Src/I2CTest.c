#include "I2CTest.h"

#define	I2CREAD		1	//I2C读操作
#define	I2CWRITE	0	//I2C写操作

#define	STARTBIT	0	
#define	RESTARTBIT	1
#define	STOPBIT		2

#define DEVICE_ADD	0x0a	//从机地址
#define ADDRLEN	1		//地址长度

uint8_t I2C_Send_Bit(uint8_t BIT_def ) 
{
	
	switch(BIT_def)
	{
		case STARTBIT:
					FL_I2C_Master_EnableI2CStart(I2C);
					while(!FL_I2C_Master_IsActiveFlag_Start(I2C));
			break;
		
		case RESTARTBIT:
					FL_I2C_Master_EnableI2CRestart(I2C);
					while(!FL_I2C_Master_IsActiveFlag_Start(I2C));		
			break;
		
		case STOPBIT:
					FL_I2C_Master_EnableI2CStop(I2C);
					while(!FL_I2C_Master_IsActiveFlag_Stop(I2C));		
			break;
		
		default:
			break;
	}
		
	return 0; //ok

}

uint8_t I2C_Send_Byte( uint8_t x_byte ) 
{

	FL_I2C_Master_WriteTXBuff(I2C,x_byte);

	while(!FL_I2C_Master_IsActiveFlag_TXComplete(I2C));
	FL_I2C_Master_ClearFlag_TXComplete(I2C);

	if(!FL_I2C_Master_IsActiveFlag_NACK(I2C))
	{
		return 0;
	}
	else
	{
		FL_I2C_Master_ClearFlag_NACK(I2C);
		return 1;
	}

}


uint8_t Sendaddr( uint16_t Device, uint8_t AddrLen, uint8_t Opt ) 
{
	uint16_t result, Devi_Addr;
	
	Devi_Addr = Device;


	if( Opt == I2CREAD ) //读操作
	{
	//-------------- start bit -------------
	result = I2C_Send_Bit( STARTBIT );//发送起始位
	if( result != 0 ) return 1; //failure.
	
	//-------------- disable read -------------
	FL_I2C_Master_DisableRX(I2C);
	//-------------- device addr -------------
	if(AddrLen == 2)					
	{
		result = I2C_Send_Byte((((Devi_Addr&0x300)>>7)| 0XF0)|1); 
		if( result != 0 ) return 2; //failure.
		result = I2C_Send_Byte( Devi_Addr&0xFF ); 
		if( result != 0 ) return 2; //failure.
	}
	else
	{
		result = I2C_Send_Byte( Devi_Addr << 1 | 1 ); 
		if( result != 0 ) return 2; //failure
	}
	}

	
	if( Opt == I2CWRITE ) //写操作
	{
	//-------------- start bit -------------
	result = I2C_Send_Bit( STARTBIT );//发送起始位
	if( result != 0 ) return 1; //failure.
	
	//-------------- disable read -------------
	FL_I2C_Master_DisableRX(I2C);
	//-------------- device addr -------------
	if(AddrLen == 2)					
	{
		result = I2C_Send_Byte(((Devi_Addr&0x300)>>7)| 0XF0);  
		if( result != 0 ) return 2; //failure.
		result = I2C_Send_Byte( Devi_Addr&0xFF ); 
		if( result != 0 ) return 2; //failure.
	}
	else
	{
		result = I2C_Send_Byte( Devi_Addr << 1 | 0 ); 
		if( result != 0 ) return 2; //failure
	}
	}	
		
	return 0; //ok
}


uint8_t I2C_Write_Bottom(uint16_t Device, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t k, n, status;
	
	if(Len > 128) return 0xFF;//一次最多操作128字节
	
	for( k=0; k<3; k++ )//每遍最多写3次
	{                                   	
		status = 0;
		if( Sendaddr( Device, AddrLen, I2CWRITE ) ) 
		{
		  status = 1; //写入失败
		}
		else 
		{
			for( n=0; n<Len; n++ )
			{
				//发送一个字节
				if( I2C_Send_Byte( Buf[n] ) ) 
				{
				  status = 1; 
				  break;
				} //写入失败
			}
		}
		//发送停止位
		if( I2C_Send_Bit( STOPBIT ) ) 
			status = 1;
		
		if( status == 0 ) 
		{
		  break;
		} //写正确
	}
	
	return( status );
}


uint8_t Test_I2C(void)
{
	uint16_t Device = DEVICE_ADD;
	uint8_t AddrLen = ADDRLEN;
	uint8_t Buf[3];
	uint8_t Len = 0;
	uint8_t Result = 0;
	
	uint8_t TestData[3] = {0x55,0xaa,0x55}; 
	
	Len = 3;
	
	memset(Buf, 0x55, 3);
	memcpy(Buf, TestData, 3);
	Result = I2C_Write_Bottom(Device, AddrLen, Buf, Len);
	
	return Result;
}
