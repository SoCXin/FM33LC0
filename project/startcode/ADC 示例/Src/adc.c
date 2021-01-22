#include "adc.h"
#include "user_init.h"

#define ADC_VREF    (*((uint16_t *)(0x1FFFFB08)))   // 30�� vref1.22����ֵ

uint64_t GetVSample;
uint32_t Get122VSample;
uint32_t GetV;

void AdcInit(void)
{
LL_GPIO_InitTypeDef         GPIO_InitStruct;	
LL_ADC_CommonInitTypeDef    ADC_CommonInitStruct;
LL_ADC_InitTypeDef          ADC_InitStruct ;

	//��������Ϊģ�⹦��
	//ADC ADC_0 ���� PC9 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//ADC ADC_1 ���� PC10 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	//ADC ADC_2 ���� PD11 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_11;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//ADC ADC_3 ���� PD0 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_0;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	//ADC ADC_4 ���� PD1 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_1;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//ADC ADC_5 ���� PD2 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_2;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	//ADC ADC_6 ���� PA13 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_13;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//ADC ADC_7 ���� PD14 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_14;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//ADC ADC_8 ���� PC7 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_7;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//ADC ADC_9 ���� PC8 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_8;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//ADC ADC_10 ���� PA15 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_15;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//ADC ADC_11 ���� PC6 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_6;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	//ADC ʱ������
	ADC_CommonInitStruct.AdcClockSource    = LL_RCC_ADC_OPERATION_CLOCK_PRESCALLER_RCHF; //RCHF
	ADC_CommonInitStruct.AdcClockPrescaler = LL_RCC_ADC_OPERATION_CLOCK_PRESCALER_DIV16; //16��Ƶ
	LL_ADC_CommonInit(&ADC_CommonInitStruct);
	
	//ADC �Ĵ�������
	  ADC_InitStruct.ADC_ContinuousConvMode  = LL_ADC_CONV_SINGLE;//����ģʽ
    ADC_InitStruct.ADC_AutoMode            = LL_ADC_SINGLE_CONV_MODE_AUTO;//�Զ�
    ADC_InitStruct.ADC_ScanDirection       = LL_ADC_SEQ_SCAN_DIR_FORWARD;//ͨ������ɨ��
    ADC_InitStruct.ADC_ExternalTrigConv    = LL_ADC_EXT_TRIGGER_NONE;//��ֹ�����ź�
    ADC_InitStruct.ADC_OverrunMode 		   = LL_ADC_OVR_DATA_OVERWRITTEN;//�����ϴ�����
    ADC_InitStruct.ADC_WaitMode 		       = LL_ADC_WAIT_MODE_NO_WAIT;//�޵ȴ� 
    ADC_InitStruct.ADC_SamplingStartControl = LL_ADC_SAMPLING_START_CONTROL_BY_REG;//��START�Ĵ�������ADC����
    ADC_InitStruct.ADC_SamplingTimeControl = LL_ADC_SAMPLING_TIME_CONTROL_BY_REG;//�ɼĴ�������ADC����ʱ��
    ADC_InitStruct.ADC_Channel_Swap_Wiat   = LL_ADC_SAMPLEING_INTERVAL_11_CYCLES;//ͨ���л��ȴ�ʱ��
    ADC_InitStruct.ADC_Channel_Fast_Time   = LL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK;//����ͨ������ʱ��
    ADC_InitStruct.ADC_Channel_Slow_Time   = LL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK;//����ͨ������ʱ��
    ADC_InitStruct.ADC_Oversampling        = DISABLE;//�������ر�
    ADC_InitStruct.ADC_OverSampingRatio    = LL_ADC_OVERSAMPLING_256X;//256��������
    ADC_InitStruct.ADC_OversamplingShift   = LL_ADC_OVERSAMPLING_RESULT_DIV256;//��������, /256	
    LL_ADC_Init(ADC, &ADC_InitStruct);

}

uint32_t GetVref1p22Sample(void)
{
uint16_t ADCRdresult;

    LL_VREF_EnableVREFBuffer(VREF);//ʹ��VREF BUFFER
	
	LL_ADC_EnalbleSequencerChannel(ADC, LL_ADC_INTERNAL_CH_VREF);//ͨ��ѡ��VREF
	
	LL_ADC_ClearFlag_EOC(ADC);//���־			
    LL_ADC_Enable(ADC);   	 // ����ADC
	LL_ADC_StartConversion(ADC);  // ��ʼת��

    // �ȴ�ת�����
    while (LL_ADC_IsActiveFlag_EOC(ADC) == RESET);
    LL_ADC_ClearFlag_EOC(ADC);//���־
	ADCRdresult =LL_ADC_ReadConversionData12(ADC);//��ȡ����ֵ
	
	LL_ADC_DisableSequencerChannel(ADC, LL_ADC_INTERNAL_CH_VREF);//ͨ���ر�VREF	
    LL_ADC_Disable(ADC);    // �ر�ADC

    LL_VREF_DisableVREFBuffer(VREF);//�ر�VREF BUFFER	
		
    // ת����� 
    return ADCRdresult;
}

uint32_t GetVoltageSample(void)
{
uint16_t ADCRdresult;
	
	LL_ADC_EnalbleSequencerChannel(ADC, LL_ADC_EXTERNAL_CH_0);//ͨ��ѡ��ADC_0
	
	LL_ADC_ClearFlag_EOC(ADC);//���־			
    LL_ADC_Enable(ADC);   	 // ����ADC
	LL_ADC_StartConversion(ADC);  // ��ʼת��

    // �ȴ�ת�����
    while (LL_ADC_IsActiveFlag_EOC(ADC) == RESET);
    LL_ADC_ClearFlag_EOC(ADC);//���־
	ADCRdresult =LL_ADC_ReadConversionData12(ADC);//��ȡ����ֵ
	LL_ADC_DisableSequencerChannel(ADC, LL_ADC_EXTERNAL_CH_0);//ͨ���ر�ADC_0
    LL_ADC_Disable(ADC);    // �ر�ADC
		
    // ת����� 
    return ADCRdresult;
}

uint32_t GetVoltage(void)
{
	Get122VSample = GetVref1p22Sample();		
	GetVSample =GetVoltageSample(); 			
	GetV =  (GetVSample *1000*(ADC_VREF*3))/(Get122VSample*4095); 
	return GetV;
}


