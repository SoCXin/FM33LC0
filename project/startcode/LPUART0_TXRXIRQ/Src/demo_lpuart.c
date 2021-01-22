#include "demo_lpuart.h"

//LPUART0 �жϴ�����
void LPUART0_IRQHandler(void)
{
uint8_t temp;

    //LPUART0�����жϴ���
    if((ENABLE == FL_LPUART_IsEnabledIT_RXWakeup(LPUART0))
        &&(SET == FL_LPUART_IsActiveFlag_RXWakeup(LPUART0)))//�����ж�
    {
        FL_LPUART_ClearFlag_RXWakeup(LPUART0);//�廽���жϱ�־
        temp = FL_LPUART_ReadRXBuff(LPUART0); //�������� 
        FL_LPUART_WriteTXBuff(LPUART0,temp);  //�����յ�������д�뷢��buff  
    } 
	
	//LPUART0�����жϴ���
	if((ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART0))
		&&(SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0)))//��������ƥ���ж�
	{
		temp = FL_LPUART_ReadRXBuff(LPUART0); //��������
        FL_LPUART_WriteTXBuff(LPUART0,temp);  //�����յ�������д�뷢��buff     
	}
	
	//LPUART0�����жϴ���
	if((ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART0))
		&&(SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART0)))
	{
		//��������жϱ�־
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART0);
	}
}

//LPUART1 �жϴ�����
void LPUART1_IRQHandler(void)
{
uint8_t temp;
    
    //LPUART1�����жϴ���	
    if((ENABLE == FL_LPUART_IsEnabledIT_RXWakeup(LPUART1))
        &&(SET == FL_LPUART_IsActiveFlag_RXWakeup(LPUART1)))//�����ж�
    {
        FL_LPUART_ClearFlag_RXWakeup(LPUART1);//�廽���жϱ�־
        temp = FL_LPUART_ReadRXBuff(LPUART1); //��������   
        FL_LPUART_WriteTXBuff(LPUART1,temp);  //�����յ�������д�뷢��buff  
    }    
    
	//LPUART1�����жϴ���
	if((ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART1))
		&&(SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART1)))//��������ƥ���ж�
	{
		temp = FL_LPUART_ReadRXBuff(LPUART1);  //��������
        FL_LPUART_WriteTXBuff(LPUART1,temp);   //�����յ�������д�뷢��buff     
	}
	
	//LPUART1�����жϴ���
	if((ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART1))
		&&(SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART1)))
	{
		//��������жϱ�־
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART1);
	}
}



//LPUART0 ��ѯ�շ�����,��һ���ֽ�,����������ֽڷ��ͳ�ȥ
void LPUART0_Test(void)
{
uint8_t temp;
	
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0))		//�ȴ����յ�һ���ֽ�
    { 
        temp = FL_LPUART_ReadRXBuff(LPUART0);		//LPUART��������
        FL_LPUART_ClearFlag_RXBuffFull(LPUART0);    
        while(FL_LPUART_IsActiveFlag_TXBuffEmpty(LPUART0)==RESET);//�ȴ���������    
        FL_LPUART_WriteTXBuff(LPUART0,temp);//����������д�뷢�ͼĴ���
    } 
}

//LPUART1 ��ѯ�շ�����,��һ���ֽ�,����������ֽڷ��ͳ�ȥ
void LPUART1_Test(void)
{
uint8_t temp;
	
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART1))		//�ȴ����յ�һ���ֽ�
    { 
        temp = FL_LPUART_ReadRXBuff(LPUART1);		//LPUART��������
        FL_LPUART_ClearFlag_RXBuffFull(LPUART1);    
        while(FL_LPUART_IsActiveFlag_TXBuffEmpty(LPUART1)==RESET);//�ȴ���������    
        FL_LPUART_WriteTXBuff(LPUART1,temp);//����������д�뷢�ͼĴ���
    } 
}



