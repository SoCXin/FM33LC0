#include "demo_lpuart.h"

//LPUART0 中断处理函数
void LPUART0_IRQHandler(void)
{
uint8_t temp;

    //LPUART0唤醒中断处理
    if((ENABLE == FL_LPUART_IsEnabledIT_RXWakeup(LPUART0))
        &&(SET == FL_LPUART_IsActiveFlag_RXWakeup(LPUART0)))//唤醒中断
    {
        FL_LPUART_ClearFlag_RXWakeup(LPUART0);//清唤醒中断标志
        temp = FL_LPUART_ReadRXBuff(LPUART0); //接收数据 
        FL_LPUART_WriteTXBuff(LPUART0,temp);  //将接收到的数据写入发送buff  
    } 
	
	//LPUART0接收中断处理
	if((ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART0))
		&&(SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0)))//接收数据匹配中断
	{
		temp = FL_LPUART_ReadRXBuff(LPUART0); //接收数据
        FL_LPUART_WriteTXBuff(LPUART0,temp);  //将接收到的数据写入发送buff     
	}
	
	//LPUART0发送中断处理
	if((ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART0))
		&&(SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART0)))
	{
		//清除发送中断标志
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART0);
	}
}

//LPUART1 中断处理函数
void LPUART1_IRQHandler(void)
{
uint8_t temp;
    
    //LPUART1唤醒中断处理	
    if((ENABLE == FL_LPUART_IsEnabledIT_RXWakeup(LPUART1))
        &&(SET == FL_LPUART_IsActiveFlag_RXWakeup(LPUART1)))//唤醒中断
    {
        FL_LPUART_ClearFlag_RXWakeup(LPUART1);//清唤醒中断标志
        temp = FL_LPUART_ReadRXBuff(LPUART1); //接收数据   
        FL_LPUART_WriteTXBuff(LPUART1,temp);  //将接收到的数据写入发送buff  
    }    
    
	//LPUART1接收中断处理
	if((ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART1))
		&&(SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART1)))//接收数据匹配中断
	{
		temp = FL_LPUART_ReadRXBuff(LPUART1);  //接收数据
        FL_LPUART_WriteTXBuff(LPUART1,temp);   //将接收到的数据写入发送buff     
	}
	
	//LPUART1发送中断处理
	if((ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART1))
		&&(SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART1)))
	{
		//清除发送中断标志
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART1);
	}
}



//LPUART0 查询收发程序,收一个字节,立即将这个字节发送出去
void LPUART0_Test(void)
{
uint8_t temp;
	
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0))		//等待接收到一个字节
    { 
        temp = FL_LPUART_ReadRXBuff(LPUART0);		//LPUART接收数据
        FL_LPUART_ClearFlag_RXBuffFull(LPUART0);    
        while(FL_LPUART_IsActiveFlag_TXBuffEmpty(LPUART0)==RESET);//等待缓冲器空    
        FL_LPUART_WriteTXBuff(LPUART0,temp);//将发送数据写入发送寄存器
    } 
}

//LPUART1 查询收发程序,收一个字节,立即将这个字节发送出去
void LPUART1_Test(void)
{
uint8_t temp;
	
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART1))		//等待接收到一个字节
    { 
        temp = FL_LPUART_ReadRXBuff(LPUART1);		//LPUART接收数据
        FL_LPUART_ClearFlag_RXBuffFull(LPUART1);    
        while(FL_LPUART_IsActiveFlag_TXBuffEmpty(LPUART1)==RESET);//等待缓冲器空    
        FL_LPUART_WriteTXBuff(LPUART1,temp);//将发送数据写入发送寄存器
    } 
}



