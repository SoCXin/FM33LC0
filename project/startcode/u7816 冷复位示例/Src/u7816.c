#include "main.h"
#include "u7816.h"
#include "user_init.h"	


//定义Netu延时，传输1个bit的时间
void Delay_Netu( unsigned char Num ) //Num*1etu
{
   DelayUs(93*Num);	//1 etu=93 us(4M),或者1 etu=186 us(2M)    
// DelayUs(104*Num);	 
}

//复位响应数据时间为400/f~40000/f即100us~10ms
//返回值: 1为下降沿; 0为无变化
uint8_t Judge_Edge(void)                                 //判定沿
{
	uint32_t i;
	Delay_Netu(1);
	for(i=0; i<100; i++) //约10ms(4M),或者20ms(2M)
	{
		if(SET == FL_U7816_IsActiveFlag_RXBusy(U7816)) //1=处于数据接收状态，收到起始位置1，收到停止位清零
		{
		  return 1;    //下降沿
		}
		else
		{
		  Delay_Netu(1);
		}
	}
		
  return 0;         //无变化
}

//最长时间应为9600etu,目前为9600etu,1etu=93us
uint8_t Get_7816_Char(unsigned char *Data)
{
	uint32_t i;	
    for(i=0x00; i<10000; i++) 	//约900ms(4M),或者1800ms(2M)
	{
//  IWDT_Clr();
	Delay_Netu(1);
	if(SET == FL_U7816_IsActiveFlag_RXComplete(U7816)) //RX_FLAG已经置位
		{
		  *Data = FL_U7816_ReadRXBuff(U7816);
	return 1; //成功
		}
	if(SET == FL_U7816_IsActiveFlag_Error(U7816)) //ERROR_FLAG已经置位
		{
		  FL_U7816_ClearFlag_TXParityError(U7816);
          FL_U7816_ClearFlag_RXParityError(U7816);
          FL_U7816_ClearFlag_RXFrameError(U7816); //接收帧格式错误
          FL_U7816_ClearFlag_RXOverflow(U7816);
			
	return 2; //error
		}
	}
	return 3;
}

uint8_t Snd_7816_Byte( unsigned char Data )
{
	uint32_t i;

	Delay_Netu(2); //延时2个etu,保证从设备稳定工作

	FL_U7816_WriteTXBuff(U7816,Data); //将待发送数据写入write buffer，自动发送
	
	for( i=0x00; i<400; i++ ) //约39ms(4M),或者78ms(2M)
	{
//    IWDT_Clr();
     Delay_Netu(1);
      if(SET == FL_U7816_IsActiveFlag_TXBuffEmpty(U7816)) //TX_FLAG置位
		 {
		   return 0; //数据发送成功
		 }
	  if(SET == FL_U7816_IsActiveFlag_Error(U7816))	//ERROR_FLAG置位
		 {
		  FL_U7816_ClearFlag_TXParityError(U7816); //清TxParityError标志，使U7816ERR中相应的错误标志清零
          FL_U7816_ClearFlag_RXParityError(U7816);        
          FL_U7816_ClearFlag_RXFrameError(U7816); 
          FL_U7816_ClearFlag_RXOverflow(U7816);
             
		  return 1; //error
		 }
	}
	
	return 1;
}

//触点激活&冷复位
//检测到卡插入后, RST置低电平, VCC上电, 延时一段时间, IO设置为输入态, CLK输出时钟信号(T0时刻)
//在T0后40000~45000个CLK内, 将RST置为高电平(T1时刻), 在T1后的400~40000个CLK内, 复位应答应该开始, 
//若IC卡的复位应答没有在此时间段内开始, 终端将启动释放时序.若收到复位应答, 但不符合协议规范, 则需要热复位
uint8_t ColdReset(void)
{
	uint8_t n, Result, Temp_ATR; // T0, TD1, TD2;        
	uint8_t cardRst8B[13];	//CARD复位信息中后13字节            
	
	DelayMs(100);//延时100ms
  
    FL_U7816_EnableTX(U7816); //通道发送使能
	FL_U7816_EnableClockOutput(U7816);
	//----------------------------------------------------------------------------------------------
	FL_GPIO_ResetOutputPin(GPIOC,FL_GPIO_PIN_10);		//将PC10引脚拉低，RST输出低电平，
	
	//RST时间保持在40000~45000个CLK;4M频率下应该保持不少于10ms;
	DelayMs(11);
	//-------- T1时刻, RST输出高电平 --------
	FL_GPIO_SetOutputPin(GPIOC,FL_GPIO_PIN_10); //等待RST时间,至少400周期,即100us
	FL_U7816_EnableRX(U7816); //卡复位完成后才能启动接收,之前IO电平不稳定,
	Result = FL_U7816_ReadRXBuff(U7816);  //RX启动后, 会产生rx_flag=1, 必须通过读取RXBUF来清除此标志.
    FL_U7816_ClearFlag_TXParityError(U7816); //清TxParityError标志，使U7816ERR中相应的错误标志清零
    FL_U7816_ClearFlag_RXParityError(U7816);        
    FL_U7816_ClearFlag_RXFrameError(U7816); 
    FL_U7816_ClearFlag_RXOverflow(U7816);

	//复位拉起后400~40000个CLK内有ATR返回
	Result = Judge_Edge(); 		//40000个CLK内查看IO口的电平沿变化
	if(Result == 0) //40000个CLK后IO口没有出现下降沿
	{
		return 2;	//异常: 40000个CLK中没有收到起始位
	}
	for(n=0; n<13; n++)
	{
		Result = Get_7816_Char(&Temp_ATR ); //receive TS.
		if( Result != 1 )
		{ 
			return 3; 
		}
		cardRst8B[ n ] = Temp_ATR;
	}
	
	if(cardRst8B[0] != 0x3b)
	{
		return 3; 
	}
	
	return 0;
}

uint8_t Test_U7816(void)
{
    uint8_t sent_data[5] = {0x00,0xA4,0x00,0x00,0x02};
    uint8_t i,n,Result,temp_ATR;
    uint8_t cardReply1[1];
    uint8_t cardReply2[2];
    
    FL_U7816_EnableClockOutput(U7816); //U7816时钟输出使能   
	ColdReset();
	
	/*冷复位后，延时一段时间并清错误标志后，再与PSAM卡进行通信*/
	DelayMs(50);//延时50ms

	FL_U7816_EnableRX(U7816);
	Result = FL_U7816_ReadRXBuff(U7816); //RX启动后, 会产生rx_flag=1, 必须通过读取RXBUF来清除此标志.
		
    FL_U7816_ClearFlag_TXParityError(U7816); //清错误标志
    FL_U7816_ClearFlag_RXParityError(U7816);        
    FL_U7816_ClearFlag_RXFrameError(U7816); 
    FL_U7816_ClearFlag_RXOverflow(U7816);
	
	FL_U7816_EnableTX(U7816);
	
  /*----------------------------
	发送00 A4 00 00 02 会接收到 A4
	-----------------------------*/	
 for(i=0;i<5;i++)
	{
		 Snd_7816_Byte( sent_data[i] );
	}
	
  Result = Judge_Edge(); 		//40000个CLK内查看IO口的电平沿变化,等待数据的回发，下降沿到来时，说明回发数据
	if( Result == 0 ) //IO口没有出现下降沿
	  {
		  return 2;	//异常: 40000个CLK中没有收到起始位
	  }
	else
 	  {
	    for(n=0; n<1; n++)
	     {
		     Result=Get_7816_Char(&temp_ATR ); //receive TS.
		        if( Result != 1 )   //没有出现下降沿
		          { 
	             	return 3; //异常
	           	}
		     cardReply1[n] = temp_ATR;   
	     }
	  }
 
 if(cardReply1[0] == 0xA4 )
	{
	    Snd_7816_Byte(0x3F);
		Snd_7816_Byte(0x0);
	}	

 Result = Judge_Edge(); 		//40000个CLK内查看IO口的电平沿变化,等待数据的回发，下降沿到来时，说明回发数据
	if( Result == 0 ) //IO口没有出现下降沿
	  {
		  return 2;	//异常: 40000个CLK中没有收到起始位
	  }
	else
 	  {
	    for(n=0; n<2; n++)
	     {
		     Result=Get_7816_Char(&temp_ATR ); //receive TS.
		        if( Result != 1 )   //没有出现下降沿
		          { 
	             	return 3; //异常
	           	}
		   cardReply2[n] = temp_ATR;   
	     }
	  }	
 return 0;     
}

