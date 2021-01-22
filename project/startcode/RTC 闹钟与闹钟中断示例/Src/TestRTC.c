#include "TestRTC.h"
#include "user_init.h"


typedef struct
{     
	uint8_t			Hour;		/*!<RTC���� ʱ*/		
	uint8_t			Minute;		/*!<RTC���� ��*/
	uint8_t			Second;		/*!<RTC���� ��*/

}RTC_AlarmTmieTypeDef;



// RTC��дʱ������ж�ʾ��
void RTC_IRQHandler(void)	
{
	if(ENABLE == LL_RTC_IsEnabledIT_Alarm(RTC) &&
		 SET == LL_RTC_IsActiveFlag_Alarm(RTC))//��ѯ�����жϱ�־�Ƿ�����
	{
  		LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);
			LL_RTC_ClearFlag_Alarm(RTC);		//��������жϱ�־
	}
}

void RTC_Init(void)
{	

	LL_RTC_InitTypeDef 	 TempTime;
    
	TempTime.Year   = 0x20;
	TempTime.Month  = 0x02;
	TempTime.Day    = 0x21;	
	TempTime.Week   = 0x04;	
	TempTime.Hour   = 0x09;
	TempTime.Minute = 0x00;
	TempTime.Second = 0x00;	
	LL_RTC_Init(RTC,&TempTime);

}



void Test_RTC_Alarm(void)
{

	RTC_AlarmTmieTypeDef 	 Alarm;
	
	RTC_Init();
	Alarm.Hour   = 0x09;
	Alarm.Minute = 0x00;
	Alarm.Second = 0x10;
	LL_RTC_SetHours_Alarm(RTC,Alarm.Hour);
	LL_RTC_SetMinutes_Alarm(RTC,Alarm.Minute);
	LL_RTC_SetSecond_Alarm(RTC,Alarm.Second);
	
	
	LL_RTC_ClearFlag_Alarm(RTC);		//��������жϱ�־
	LL_RTC_EnableIT_Alarm(RTC);
	NVIC_DisableIRQ(RTC_IRQn);				//NVIC�жϿ���������
	NVIC_SetPriority(RTC_IRQn,2);
	NVIC_EnableIRQ(RTC_IRQn);	
}

