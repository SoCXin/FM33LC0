#include "I2CTest.h"

#define	I2CREAD		1	//I2C读操作
#define	I2CWRITE	0	//I2C写操作

#define	STARTBIT	0	
#define	RESTARTBIT	1
#define	STOPBIT		2

#define DEVICE_FM38025T     0x64	//FM38025T的器件地址
#define ADDRLEN_FM38025T	1		//FM38025T的地址长度

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

uint8_t I2C_Receive_Byte( uint8_t *x_byte ) 
{

	//i2c en, rcen
	FL_I2C_Master_EnableRX(I2C);
	while(!FL_I2C_Master_IsActiveFlag_RXComplete(I2C));
	FL_I2C_Master_ClearFlag_RXComplete(I2C);
	*x_byte=FL_I2C_Master_ReadRXBuff(I2C);
	return 0;
}

uint8_t Sendaddr( uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t Opt ) 
{
	uint8_t result, Devi_Addr;
	
	Devi_Addr = Device;


	//-------------- start bit -------------
	result = I2C_Send_Bit( STARTBIT );//发送起始位
	if( result != 0 ) return 1; //failure.
	
	//-------------- disable read -------------
	FL_I2C_Master_DisableRX(I2C);
	//-------------- device addr -------------
	result = I2C_Send_Byte( Devi_Addr ); //发送器件地址 
	if( result != 0 ) return 2; //failure.

	//--------------- data addr --------------
	if(AddrLen == 2)
	{
		result = I2C_Send_Byte( Addr>>8 ); //发送数据地址高8位
		if( result != 0 ) return 3; //failure.
	}
	result = I2C_Send_Byte( Addr>>0 ); //发送数据地址低8位
	if( result != 0 ) return 3; //failure.

	if( Opt == I2CREAD ) //读操作
	{
		result = I2C_Send_Bit( RESTARTBIT ); //发送重起始位
		if( result != 0 ) return 5; //failure.
		
		result = I2C_Send_Byte( Devi_Addr|1 ); //发送器件地址，读取
		if( result != 0 ) return 5; //failure.
	}
		
	return 0; //ok
}


uint8_t Wait_for_end( uint8_t Device )
{
	uint8_t result, Devi_Addr;

	Devi_Addr = Device;
	
	SysTick->LOAD = 0x1000000-1;
    SysTick->VAL = 0; 
	Do_DelayStart(); //需要5ms的内部写周期
	{
		I2C_Send_Bit( STARTBIT );	//发送起始位

		result = I2C_Send_Byte( Devi_Addr ); //发送器件地址

		I2C_Send_Bit( STOPBIT ); //发送停止位

		if( result == 0 ) return 0; //设置地址成功，写周期结束
    
	}While_DelayMsEnd(5);

	return 1; //设置地址失败
}

uint8_t I2C_Write_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t k, n, status;
	
	if(Len > 128) return 0xFF;//一次最多操作128字节
	
	for( k=0; k<3; k++ )//每遍最多写3次
	{                                   	
		status = 0;
		if( Sendaddr( Device, Addr, AddrLen, I2CWRITE ) ) 
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
		  Wait_for_end(Device);
		  break;
		} //写正确
	}
	
	return( status );
}


uint8_t I2C_Read_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t k, n, status;
	
	if(Len > 128) return 0xFF;//一次最多操作128字节
	
	for( k=0; k<3; k++ )//每遍最多读3次
	{
		status = 0;
		if( Sendaddr( Device, Addr, AddrLen, I2CREAD ) )
      status = 1; //写入失败
		else 
		{
			for( n=0; n<Len; n++ )
			{
				if( n < (Len-1) )
					FL_I2C_Master_SetRespond(I2C,FL_I2C_MASTER_RESPOND_ACK);
				else
					FL_I2C_Master_SetRespond(I2C,FL_I2C_MASTER_RESPOND_NACK);
				
				//接受一个字节
				if( I2C_Receive_Byte( Buf+n ) ) 
        {
          status = 1; 
          break;
        } 
	
			}
		}
		//发送停止位
		if( I2C_Send_Bit( STOPBIT ) ) 
      status = 1;	//失败
		
		if( status == 0 ) break;//读正确
	}
	
	return( status );
}


uint8_t I2CTest(void)
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
	
	
	memset(Buf, 0, 64);
	Result = I2C_Read_Bottom(Device, Addr, AddrLen, Buf, Len);
	
	memset(Buf, 0x55, 64);
	memcpy(Buf, TestData, Len);
	Result = I2C_Write_Bottom(Device, Addr, AddrLen, Buf, Len);
	
	memset(Buf, 0, 64);
	Result = I2C_Read_Bottom(Device, Addr, AddrLen, Buf, Len);
	

	return Result;
}

