#include "adc.h"
#include "user_init.h"
#include "FreeRTOS.h"
#include "task.h"


uint8_t ADCComplete=0;
void ADC_IRQHandler(void)
{
	
	if((ENABLE == FL_ADC_IsEnabledIT_EndOfConversion(ADC))
		&&(SET == FL_ADC_IsActiveFlag_EndOfConversion(ADC)))
	{
		FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志
		ADCComplete = 1;
	
	}

}


static uint32_t GetVREF1P2Sample_POLL(void)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVREFBuffer(VREF);//使能VREF BUFFER
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//通道选择VREF
            
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志			
    FL_ADC_Enable(ADC);   	 // 启动ADC
    FL_ADC_EnableSWConversion(ADC);  // 开始转换
    // 等待转换完成
    while (FL_ADC_IsActiveFlag_EndOfConversion(ADC) == RESET)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//获取采样值

    FL_ADC_Disable(ADC);    // 关闭ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//通道关闭VREF	
    FL_VREF_DisableVREFBuffer(VREF);//关闭VREF BUFFER			
    // 转换结果 
    return ADCRdresult;
}

static uint32_t GetVREF1P2Sample_IT(void)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVREFBuffer(VREF);//使能VREF BUFFER
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//通道选择VREF
            
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志			
    FL_ADC_Enable(ADC);   	 // 启动ADC
    FL_ADC_EnableSWConversion(ADC);  // 开始转换
    // 等待转换完成
    while (ADCComplete == 0)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    ADCComplete = 0;
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//获取采样值

    FL_ADC_Disable(ADC);    // 关闭ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//通道关闭VREF	
    FL_VREF_DisableVREFBuffer(VREF);//关闭VREF BUFFER			
    // 转换结果 
    return ADCRdresult;
}



static uint32_t GetSingleChannelSample_POLL(uint32_t channel)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV1);
    FL_ADC_EnableSequencerChannel(ADC, channel);//通道选择

    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志			
    FL_ADC_Enable(ADC);   	 // 启动ADC
    FL_ADC_EnableSWConversion(ADC);  // 开始转换
    // 等待转换完成
    while (FL_ADC_IsActiveFlag_EndOfConversion(ADC) == RESET)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//获取采样值

    FL_ADC_Disable(ADC);    // 关闭ADC
    FL_ADC_DisableSequencerChannel(ADC, channel);//通道	 	 
    // 转换结果 
    return ADCRdresult;
}

static uint32_t GetSingleChannelSample_IT(uint32_t channel)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV1);
    FL_ADC_EnableSequencerChannel(ADC, channel);//通道选择

    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志			
    FL_ADC_Enable(ADC);   	 // 启动ADC
    FL_ADC_EnableSWConversion(ADC);  // 开始转换
    // 等待转换完成
    while (ADCComplete == 0)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    ADCComplete = 0;
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//获取采样值

    FL_ADC_Disable(ADC);    // 关闭ADC
    FL_ADC_DisableSequencerChannel(ADC, channel);//通道	 	 
    // 转换结果 
    return ADCRdresult;
}


static uint32_t GetTSSample_POLL(void)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVPTATBuffer(VREF);
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);//通道选择

    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志			
    FL_ADC_Enable(ADC);   	 // 启动ADC
    FL_ADC_EnableSWConversion(ADC);  // 开始转换
    // 等待转换完成
    while (FL_ADC_IsActiveFlag_EndOfConversion(ADC) == RESET)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    FL_ADC_ClearFlag_EndOfConversion(ADC);//清标志
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//获取采样值

    FL_ADC_Disable(ADC);    // 关闭ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);//通道
    FL_VREF_DisableVPTATBuffer(VREF);	
    // 转换结果 
    return ADCRdresult;
}

uint32_t GetSingleChannelVoltage_POLL(uint32_t channel)
{
    uint32_t Get122VSample,GetChannelVoltage;
    uint64_t GetVSample; 

    Get122VSample = GetVREF1P2Sample_POLL();
    GetVSample =GetSingleChannelSample_POLL(channel);
    GetChannelVoltage =  (GetVSample *3000*(ADC_VREF))/(Get122VSample*4095);
    // 转换结果 
    return GetChannelVoltage;
}

float GetTS_POLL(void)
{
    uint32_t Get122VSample,VPTAT,VPTAT_30;
    uint64_t GetTSSample;
    float GetTS; 

    Get122VSample = GetVREF1P2Sample_POLL();
    GetTSSample =GetTSSample_POLL();
    VPTAT = (GetTSSample *3000*(ADC_VREF))/(Get122VSample*4095); 
    VPTAT_30 = (ADC_TS *3000)/(4095); 	

    GetTS =  (float)(VPTAT*1.0 - VPTAT_30*1.0)/(2.97)+30-2;
    // 转换结果 
    return GetTS;
}

uint32_t GetSingleChannelVoltage_IT(uint32_t channel)
{
    uint32_t Get122VSample,GetChannelVoltage;
    uint64_t GetVSample; 

    Get122VSample = GetVREF1P2Sample_IT();
    GetVSample =GetSingleChannelSample_IT(channel);
    GetChannelVoltage =  (GetVSample *3000*(ADC_VREF))/(Get122VSample*4095);
    // 转换结果 
    return GetChannelVoltage;
}

uint16_t ADCbuffer[3]={0,0,0};
void GetConvertSample(void)
{ 
	
	ADCbuffer[0] =GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0);//获取采样值
    ADCbuffer[1] =GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0);//获取采样值
    ADCbuffer[2] =GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0);//获取采样值

}
