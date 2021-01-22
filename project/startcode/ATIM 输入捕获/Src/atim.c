#include "atim.h"
#include "main.h"

void ATIM_Init(void)
{
    LL_ATIM_InitTypeDef        InitStructer;    
    
    InitStructer.ClockSource           = LL_RCC_ATIME_OPERATION_CLOCK_SOURCE_APBCLK2;  //ʱ��Դѡ��APB2
    InitStructer.Prescaler             = 7999;                                         //��Ƶϵ��8000
    InitStructer.CounterMode           = LL_ATIM_COUNTER_DIRECT_UP;                    //���ϼ���
    InitStructer.Autoreload            = 999;                                          //�Զ���װ��ֵ1000
    InitStructer.ClockDivision         = LL_ATIM_CLOCKDIVISION_DIV1;                   //�������˲�����
    InitStructer.RepetitionCounter     = 0;                                            //�ظ�����
    InitStructer.AutoreloadState       = DISABLE;                                      //�Զ���װ�ؽ�ֹpreload
    LL_ATIM_Init(ATIM,&InitStructer);
    
    NVIC_DisableIRQ(ATIM_IRQn);
    NVIC_SetPriority(ATIM_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(ATIM_IRQn);	
  
    LL_ATIM_ClearFlag_UPDATE(ATIM);  //����������жϱ�־λ
  
    LL_ATIM_EnableIT_UPDATE(ATIM); //�����������ж�
 
    LL_ATIM_EnableCounter(ATIM); //ʹ�ܶ�ʱ��
}

void ATIM_PWM_Init(void)
{
    LL_ATIM_InitTypeDef        InitStructer1;    
    LL_ATIM_OC_InitTypeDef     InitStructer2;
    LL_ATIM_BDTR_InitTypeDef   InitStructer3;
    LL_GPIO_InitTypeDef         GPIO_InitStruct={0};
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = DISABLE;
    LL_GPIO_Init(GPIOB,&GPIO_InitStruct);  //CH1 
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = ENABLE;
    LL_GPIO_Init(GPIOB,&GPIO_InitStruct);  //CH1N
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.RemapPin = ENABLE;
    LL_GPIO_Init(GPIOD,&GPIO_InitStruct); //BRK1
    
    InitStructer1.ClockSource           = LL_RCC_ATIME_OPERATION_CLOCK_SOURCE_APBCLK2;  //ʱ��Դѡ��APB2
    InitStructer1.Prescaler             = 7999;                                         //��Ƶϵ��8000
    InitStructer1.CounterMode           = LL_ATIM_COUNTER_DIRECT_UP;                    //���ϼ���
    InitStructer1.Autoreload            = 999;                                          //�Զ���װ��ֵ1000
    InitStructer1.ClockDivision         = LL_ATIM_CLOCKDIVISION_DIV1;                   //�������˲���Ƶ
    InitStructer1.RepetitionCounter     = 0;                                            //�ظ�����
    InitStructer1.AutoreloadState       = ENABLE;                                       //Ԥװ��preloadʹ��                        
    LL_ATIM_Init(ATIM,&InitStructer1);
    
    InitStructer2.OCMode       = LL_ATIM_OC_MODE_PWM1;                     //����Ƚ�ģʽPWM1
    InitStructer2.OCETRFStatus = DISABLE;                                  //OC1REF����ETRӰ��
    InitStructer2.OCFastMode   = DISABLE;                                  //�رտ���ʹ��  
    InitStructer2.CompareValue = 500;                                      //�Ƚ�ֵ500
    InitStructer2.OCPolarity   = LL_ATIM_OC_POLARITY_HIGH;                 //OC �ߵ�ƽ��Ч
    InitStructer2.OCPreload    = DISABLE;                                  //OC preload ��Ч
    InitStructer2.OCIdleState  = LL_ATIM_OC_IDLESTATE_HIGH;                //OC IDLEʱΪ�ߵ�ƽ
    InitStructer2.OCNIdleState = LL_ATIM_OCN_IDLESTATE_HIGH;               //OCN IDLEʱΪ�ߵ�ƽ
    InitStructer2.OCNPolarity  = LL_ATIM_OCN_POLARITY_HIGH;                //OCN �ߵ�ƽ��Ч
    InitStructer2.OCNState     = ENABLE;                                   //ʹ�ܻ������ͨ��
    LL_ATIM_OC_Init(ATIM,LL_ATIM_CHANNEL_1,&InitStructer2);
    
    InitStructer3.DeadTime            = 10;                                 //����ʱ������
    InitStructer3.LockLevel           = LL_ATIM_LOCKLEVEL_OFF;              //�Ĵ���д�����ر�
    InitStructer3.OSSRState           = LL_ATIM_OSSR_DISABLE;               //OSSR=0
    InitStructer3.OSSIState           = LL_ATIM_OSSI_DISABLE;               //OSSI=0
    InitStructer3.BreakFilter         = LL_ATIM_BRK_FILTER_FDIV1;           //ɲ���ź��˲�����
    InitStructer3.BreakPolarity       = LL_ATIM_BREAK_POLARITY_HIGH;        //ɲ���źŸߵ�ƽ��Ч
    InitStructer3.AutomaticOutput     = DISABLE;                            //MOE�������λ
    InitStructer3.GatedBrakeSignal_1  = LL_ATIM_BREAK1_GATE_AUTO;           //ɲ���ź�1���ſ�
    InitStructer3.GatedBrakeSignal_2  = LL_ATIM_BREAK2_GATE_AUTO;           //ɲ���ź�2���ſ�
    InitStructer3.BrakeSignalCombined = LL_ATIM_BRK_COMBINATION_OR;         //ɲ���ź�1��2��
    InitStructer3.BreakState          = DISABLE;                            //ɲ���źŽ�ֹ
    LL_ATIM_BDTR_Init(ATIM,&InitStructer3);
 
    LL_ATIM_EnableCounter(ATIM); //ʹ�ܶ�ʱ��
    
    LL_ATIM_Enable_AllOutputs(ATIM);//�������ʹ��
}

void ATIM_CAPTURE_Init(void)
{   
    LL_ATIM_InitTypeDef        InitStructer1;    
    LL_ATIM_IC_InitTypeDef     InitStructer2;
    LL_ATIM_SlaveInitTypeDef   InitStructer3;
    LL_GPIO_InitTypeDef         GPIO_InitStruct={0};
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = DISABLE;
    
    LL_GPIO_Init(GPIOB,&GPIO_InitStruct);  //CH1 
    
    InitStructer1.ClockSource           = LL_RCC_ATIME_OPERATION_CLOCK_SOURCE_APBCLK2;//ʱ��Դ APB2
    InitStructer1.Prescaler             = 7999;                                       //��Ƶ8000
    InitStructer1.CounterMode           = LL_ATIM_COUNTER_DIRECT_UP;                  //���ϼ���
    InitStructer1.Autoreload            = 65535;                                      //�Զ�װ��ֵ65536
    InitStructer1.ClockDivision         = LL_ATIM_CLOCKDIVISION_DIV1;                 // �����������˲���Ƶ
    InitStructer1.RepetitionCounter     = 0;                                          //�ظ�����0
    InitStructer1.AutoreloadState       = ENABLE;                                     //�Զ���װ��ARPEʹ��
    LL_ATIM_Init(ATIM,&InitStructer1);
    
    InitStructer3.SlaveMode     = LL_ATIM_SLAVE_MODE_TRGI_RISE_RST;   //�ӻ���λģʽ
    InitStructer3.TriggerSrc    = LL_ATIM_TIM_TS_TI1FP1;              //����Դѡ�� TI1FP1
    InitStructer3.TriggerDelay  = DISABLE;                            //TRGI�ӳٽ�ֹ
    LL_ATIM_SlaveMode_Init(ATIM,&InitStructer3);
    
    InitStructer2.ICPolarity    = LL_ATIM_IC_POLARITY_RISING;          //�����ز���
    InitStructer2.ICActiveInput = LL_ATIM_CC1_MODE_INPUT_TI1;          //CC1����Ϊ���룬IC1ӳ�䵽TI1
    InitStructer2.ICPrescaler   = LL_ATIM_IC_PRESCALER_DIV_1;          //���벶׽��Ƶ
    InitStructer2.ICFilter      = LL_ATIM_IC_FILTER_FDIV1;             //���벶׽�˲�����
    InitStructer2.CaptureState  = ENABLE;                              //ʹ��CC1ͨ��
    LL_ATIM_IC_Init(ATIM,LL_ATIM_CHANNEL_1,&InitStructer2);
    
    InitStructer2.ICPolarity    = LL_ATIM_IC_POLARITY_FALLING;         //�½��ز���
    InitStructer2.ICActiveInput = LL_ATIM_CC2_MODE_INPUT_TI1;          //CC2����Ϊ���룬IC1ӳ�䵽TI1
    LL_ATIM_IC_Init(ATIM,LL_ATIM_CHANNEL_2,&InitStructer2);
    
    NVIC_DisableIRQ(ATIM_IRQn);
    NVIC_SetPriority(ATIM_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(ATIM_IRQn);
    
    LL_ATIM_ClearFlag_CC(ATIM,LL_ATIM_CHANNEL_1);     //���CC1��׽��־      
    LL_ATIM_EnableIT_CC(ATIM,LL_ATIM_CHANNEL_1);      //ʹ��CC1��׽�ж�
    
    LL_ATIM_EnableCounter(ATIM); //ʹ�ܶ�ʱ��
}

