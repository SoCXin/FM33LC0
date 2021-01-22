#include "demo_rtc.h"

// RTC中断处理函数
void RTC_IRQHandler(void)
{
    //闹钟中断
    if(ENABLE == FL_RTC_IsEnabledIT_Alarm(RTC) &&
         SET == FL_RTC_IsActiveFlag_Alarm(RTC))//查询标志是否置起
    {
        FL_RTC_ClearFlag_Alarm(RTC);        //清除中断标志
    }
    //1KHz中断
	if(ENABLE == FL_RTC_IsEnabledIT_1KHz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_1KHz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_1KHz(RTC);		    //清除中断标志
	} 
    //256Hz中断
	if(ENABLE == FL_RTC_IsEnabledIT_256Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_256Hz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_256Hz(RTC);		    //清除中断标志
	} 
 
    //64Hz中断
	if(ENABLE == FL_RTC_IsEnabledIT_64Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_64Hz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_64Hz(RTC);		    //清除中断标志
	} 
    
    //16Hz中断
	if(ENABLE == FL_RTC_IsEnabledIT_16Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_16Hz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_16Hz(RTC);		    //清除中断标志
	}

    //8Hz中断
	if(ENABLE == FL_RTC_IsEnabledIT_8Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_8Hz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_8Hz(RTC);		    //清除中断标志
	}   

    //4Hz中断
	if(ENABLE == FL_RTC_IsEnabledIT_4Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_4Hz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_4Hz(RTC);		    //清除中断标志
	}   
    
    //2Hz中断
	if(ENABLE == FL_RTC_IsEnabledIT_2Hz(RTC) &&
		 SET == FL_RTC_IsActiveFlag_2Hz(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_2Hz(RTC);		    //清除中断标志
	}      
    
    // 秒中断
	if(ENABLE == FL_RTC_IsEnabledIT_Second(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Second(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_Second(RTC);		//清除中断标志
	}    

    // 分钟中断
	if(ENABLE == FL_RTC_IsEnabledIT_Minute(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Minute(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_Minute(RTC);		//清除中断标志
	}

    // 小时中断
	if(ENABLE == FL_RTC_IsEnabledIT_Hour(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Hour(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_Hour(RTC);		//清除中断标志
	}    

    // 天中断
	if(ENABLE == FL_RTC_IsEnabledIT_Day(RTC) &&
		 SET == FL_RTC_IsActiveFlag_Day(RTC))//查询标志是否置起
	{
		FL_RTC_ClearFlag_Day(RTC);		//清除中断标志
	}     
}

//RTC 闹钟中断设置 
void RTC_AlarmTimeSet(void)
{
    //关闭闹钟中断
    FL_RTC_DisableIT_Alarm(RTC);
    //设置闹钟时间
    FL_RTC_WriteHourAlarm(RTC,0x00);//时
    FL_RTC_WriteMinuteAlarm(RTC,0x00);//分
    FL_RTC_WriteSecondAlarm(RTC,0x10);//秒
    
    FL_RTC_ClearFlag_Alarm(RTC);//清除闹钟中断标志
    FL_RTC_EnableIT_Alarm(RTC);//打开闹钟中断
}

//RTC 秒时标输出， 秒时标从PD11引脚输出
void RTC_TimeMarkOut(void)
{
FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    //RTC秒时标选择
    FL_RTC_SetTimeMarkOutput(RTC,FL_RTC_TIME_MARK_SEC);//RTC 秒时标

    //PD11引脚,配置成fout0功能 
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    //FOUT0输出选择RTC时标 
    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_RTCTM);
}

//获取RTC模块的时间到 ram 
uint8_t RTC_GetRTC(FL_RTC_InitTypeDef* InitStructer)
{
	uint8_t n, i;
	uint8_t Result = 1;

	FL_RTC_InitTypeDef TempTime1,TempTime2;
	
	for(n=0 ;n<3; n++)
	{
		FL_RTC_GetTime(RTC,&TempTime1);//读一次时间
		FL_RTC_GetTime(RTC,&TempTime2);//再读一次时间
		
		for(i=0; i<7; i++)//两者一致, 表示读取成功
		{
			if(((uint32_t*)(&TempTime1))[i] != ((uint32_t*)(&TempTime2))[i]) break;
		}
		if(i == 7)
		{
			Result = 0;
			memcpy((uint32_t*)(InitStructer), (uint32_t*)(&TempTime1), 7*sizeof(uint32_t));//读取正确则更新新的时间		
			break;
		}
	}
	return Result;
}

//设置ram的时间到RTC模块
uint8_t RTC_SetRTC(FL_RTC_InitTypeDef* InitStructer)
{
	uint8_t n, i;
	uint8_t Result;
	FL_RTC_InitTypeDef TempTime1;
	
	for(n=0 ;n<3; n++)
	{
		FL_RTC_ConfigTime(RTC,InitStructer);	
		Result = RTC_GetRTC(&TempTime1);	//读取确认设置结果
		if(Result == 0)
		{
			Result = 1;
			for(i=0; i<7; i++)//两者一致, 表示设置成功
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

//读写时间测试
void RTC_ReadWrite(void)
{
	FL_RTC_InitTypeDef 	 InitTime;
	FL_RTC_InitTypeDef 	 GetTime;
	
    //在ram中设置写入的时间
	InitTime.year   = 0x20;
	InitTime.month  = 0x10;
	InitTime.day    = 0x02;	
	InitTime.week   = 0x04;	
	InitTime.hour   = 0x15;
	InitTime.minute = 0x00;
	InitTime.second = 0x00;	

    //将ram的时间 写入RTC模块
	RTC_SetRTC(&InitTime);
    
	DelayMs(1000); //延时，不是必须。可以删掉。这里为了看RTC在走时 ，所以等了1秒 
    
    //将RTC模块的时间 读出到ram
	RTC_GetRTC(&GetTime);
}


