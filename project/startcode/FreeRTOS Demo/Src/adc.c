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
		FL_ADC_ClearFlag_EndOfConversion(ADC);//���־
		ADCComplete = 1;
	
	}

}


static uint32_t GetVREF1P2Sample_POLL(void)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVREFBuffer(VREF);//ʹ��VREF BUFFER
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//ͨ��ѡ��VREF
            
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־			
    FL_ADC_Enable(ADC);   	 // ����ADC
    FL_ADC_EnableSWConversion(ADC);  // ��ʼת��
    // �ȴ�ת�����
    while (FL_ADC_IsActiveFlag_EndOfConversion(ADC) == RESET)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//��ȡ����ֵ

    FL_ADC_Disable(ADC);    // �ر�ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//ͨ���ر�VREF	
    FL_VREF_DisableVREFBuffer(VREF);//�ر�VREF BUFFER			
    // ת����� 
    return ADCRdresult;
}

static uint32_t GetVREF1P2Sample_IT(void)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVREFBuffer(VREF);//ʹ��VREF BUFFER
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//ͨ��ѡ��VREF
            
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־			
    FL_ADC_Enable(ADC);   	 // ����ADC
    FL_ADC_EnableSWConversion(ADC);  // ��ʼת��
    // �ȴ�ת�����
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
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//��ȡ����ֵ

    FL_ADC_Disable(ADC);    // �ر�ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);//ͨ���ر�VREF	
    FL_VREF_DisableVREFBuffer(VREF);//�ر�VREF BUFFER			
    // ת����� 
    return ADCRdresult;
}



static uint32_t GetSingleChannelSample_POLL(uint32_t channel)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV1);
    FL_ADC_EnableSequencerChannel(ADC, channel);//ͨ��ѡ��

    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־			
    FL_ADC_Enable(ADC);   	 // ����ADC
    FL_ADC_EnableSWConversion(ADC);  // ��ʼת��
    // �ȴ�ת�����
    while (FL_ADC_IsActiveFlag_EndOfConversion(ADC) == RESET)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//��ȡ����ֵ

    FL_ADC_Disable(ADC);    // �ر�ADC
    FL_ADC_DisableSequencerChannel(ADC, channel);//ͨ��	 	 
    // ת����� 
    return ADCRdresult;
}

static uint32_t GetSingleChannelSample_IT(uint32_t channel)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV1);
    FL_ADC_EnableSequencerChannel(ADC, channel);//ͨ��ѡ��

    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־			
    FL_ADC_Enable(ADC);   	 // ����ADC
    FL_ADC_EnableSWConversion(ADC);  // ��ʼת��
    // �ȴ�ת�����
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
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//��ȡ����ֵ

    FL_ADC_Disable(ADC);    // �ر�ADC
    FL_ADC_DisableSequencerChannel(ADC, channel);//ͨ��	 	 
    // ת����� 
    return ADCRdresult;
}


static uint32_t GetTSSample_POLL(void)
{
    uint16_t ADCRdresult;
    uint8_t i=0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVPTATBuffer(VREF);
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);//ͨ��ѡ��

    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־			
    FL_ADC_Enable(ADC);   	 // ����ADC
    FL_ADC_EnableSWConversion(ADC);  // ��ʼת��
    // �ȴ�ת�����
    while (FL_ADC_IsActiveFlag_EndOfConversion(ADC) == RESET)
    {
        if(i>=5)
        {
            break;
        }
        i++;
        vTaskDelay(1);
    }
    FL_ADC_ClearFlag_EndOfConversion(ADC);//���־
    ADCRdresult =FL_ADC_ReadConversionData(ADC);//��ȡ����ֵ

    FL_ADC_Disable(ADC);    // �ر�ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);//ͨ��
    FL_VREF_DisableVPTATBuffer(VREF);	
    // ת����� 
    return ADCRdresult;
}

uint32_t GetSingleChannelVoltage_POLL(uint32_t channel)
{
    uint32_t Get122VSample,GetChannelVoltage;
    uint64_t GetVSample; 

    Get122VSample = GetVREF1P2Sample_POLL();
    GetVSample =GetSingleChannelSample_POLL(channel);
    GetChannelVoltage =  (GetVSample *3000*(ADC_VREF))/(Get122VSample*4095);
    // ת����� 
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
    // ת����� 
    return GetTS;
}

uint32_t GetSingleChannelVoltage_IT(uint32_t channel)
{
    uint32_t Get122VSample,GetChannelVoltage;
    uint64_t GetVSample; 

    Get122VSample = GetVREF1P2Sample_IT();
    GetVSample =GetSingleChannelSample_IT(channel);
    GetChannelVoltage =  (GetVSample *3000*(ADC_VREF))/(Get122VSample*4095);
    // ת����� 
    return GetChannelVoltage;
}

uint16_t ADCbuffer[3]={0,0,0};
void GetConvertSample(void)
{ 
	
	ADCbuffer[0] =GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0);//��ȡ����ֵ
    ADCbuffer[1] =GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0);//��ȡ����ֵ
    ADCbuffer[2] =GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0);//��ȡ����ֵ

}
