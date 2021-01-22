#include "demo_rtc.h"

// RTC�жϴ�����
void RTC_IRQHandler(void)
{
    //�����ж�
    if(ENABLE == FL_RTC_IsEnabledIT_Alarm(RTC) &&
         SET == FL_RTC_IsActiveFlag_Alarm(RTC))//��ѯ��־�Ƿ�����
    {
        FL_RTC_ClearFlag_Alarm(RTC);        //����жϱ�־
    }
    //1KHz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_1KHz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_1KHz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_1KHz(RTC);		    //����жϱ�־
	} 
    //256Hz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_256Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_256Hz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_256Hz(RTC);		    //����жϱ�־
	} 
 
    //64Hz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_64Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_64Hz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_64Hz(RTC);		    //����жϱ�־
	} 
    
    //16Hz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_16Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_16Hz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_16Hz(RTC);		    //����жϱ�־
	}

    //8Hz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_8Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_8Hz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_8Hz(RTC);		    //����жϱ�־
	}   

    //4Hz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_4Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_4Hz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_4Hz(RTC);		    //����жϱ�־
	}   
    
    //2Hz�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_2Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_2Hz(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_2Hz(RTC);		    //����жϱ�־
	}      
    
    // ���ж�
	if(ENABLE == FL_RTC_IsEnabledIT_Second(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Second(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_Second(RTC);		//����жϱ�־
	}    

    // �����ж�
	if(ENABLE == FL_RTC_IsEnabledIT_Minute(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Minute(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_Minute(RTC);		//����жϱ�־
	}

    // Сʱ�ж�
	if(ENABLE == FL_RTC_IsEnabledIT_Hour(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Hour(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_Hour(RTC);		//����жϱ�־
	}    

    // ���ж�
	if(ENABLE == FL_RTC_IsEnabledIT_Day(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Day(RTC))//��ѯ��־�Ƿ�����
	{
		FL_RTC_ClearFlag_Day(RTC);		//����жϱ�־
	}     
}

//RTC �����ж����� 
void RTC_AlarmTimeSet(void)
{
    //�ر������ж�
    FL_RTC_DisableIT_Alarm(RTC);
    //��������ʱ��
    FL_RTC_WriteHourAlarm(RTC,0x00);//ʱ
    FL_RTC_WriteMinuteAlarm(RTC,0x00);//��
    FL_RTC_WriteSecondAlarm(RTC,0x10);//��
    
    FL_RTC_ClearFlag_Alarm(RTC);//��������жϱ�־
    FL_RTC_EnableIT_Alarm(RTC);//�������ж�
}

//RTC ��ʱ������� ��ʱ���PD11�������
void RTC_TimeMarkOut(void)
{
FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    //RTC��ʱ��ѡ��
    FL_RTC_SetTimeMarkOutput(RTC,FL_RTC_TIME_MARK_SEC);//RTC ��ʱ��

    //PD11����,���ó�fout0���� 
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    //FOUT0���ѡ��RTCʱ�� 
    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_RTCTM);
}

//��ȡRTCģ���ʱ�䵽 ram 
uint8_t RTC_GetRTC(FL_RTC_InitTypeDef* InitStructer)
{
	uint8_t n, i;
	uint8_t Result = 1;

	FL_RTC_InitTypeDef TempTime1,TempTime2;
	
	for(n=0 ;n<3; n++)
	{
		FL_RTC_GetTime(RTC,&TempTime1);//��һ��ʱ��
		FL_RTC_GetTime(RTC,&TempTime2);//�ٶ�һ��ʱ��
		
		for(i=0; i<7; i++)//����һ��, ��ʾ��ȡ�ɹ�
		{
			if(((uint32_t*)(&TempTime1))[i] != ((uint32_t*)(&TempTime2))[i]) break;
		}
		if(i == 7)
		{
			Result = 0;
			memcpy((uint32_t*)(InitStructer), (uint32_t*)(&TempTime1), 7*sizeof(uint32_t));//��ȡ��ȷ������µ�ʱ��		
			break;
		}
	}
	return Result;
}

//����ram��ʱ�䵽RTCģ��
uint8_t RTC_SetRTC(FL_RTC_InitTypeDef* InitStructer)
{
	uint8_t n, i;
	uint8_t Result;
	FL_RTC_InitTypeDef TempTime1;
	
	for(n=0 ;n<3; n++)
	{
		FL_RTC_ConfigTime(RTC,InitStructer);	
		Result = RTC_GetRTC(&TempTime1);	//��ȡȷ�����ý��
		if(Result == 0)
		{
			Result = 1;
			for(i=0; i<7; i++)//����һ��, ��ʾ���óɹ�
			{
				if(((uint32_t*)(&TempTime1))[i] != ((uint32_t*)(InitStructer))[i]) 
					break;
			}
			if(i == 7)
			{
				Result = 0;
				break;
			}
		}
	}
	return Result;
}

//��дʱ�����
void RTC_ReadWrite(void)
{
	FL_RTC_InitTypeDef 	 InitTime;
	FL_RTC_InitTypeDef 	 GetTime;
	
    //��ram������д���ʱ��
	InitTime.year   = 0x20;
	InitTime.month  = 0x10;
	InitTime.day    = 0x02;	
	InitTime.week   = 0x04;	
	InitTime.hour   = 0x15;
	InitTime.minute = 0x00;
	InitTime.second = 0x00;	

    //��ram��ʱ�� д��RTCģ��
	RTC_SetRTC(&InitTime);
    
	DelayMs(1000); //��ʱ�����Ǳ��롣����ɾ��������Ϊ�˿�RTC����ʱ �����Ե���1�� 
    
    //��RTCģ���ʱ�� ������ram
	RTC_GetRTC(&GetTime);
}


