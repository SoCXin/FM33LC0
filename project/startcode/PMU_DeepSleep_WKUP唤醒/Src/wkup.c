#include "user_init.h"
#include "main.h"
#include "wkup.h"

void NMI_Handler(void)
{
    //NWKUPĬ�����ӵ���cpu��NMI���������жϣ�����NVIC���ƣ�����ȫ���ж�ʹ�ܿ��ƣ����Ѻ��Ȼ��NMI�ж�
    if( SET == FL_PMU_IsActiveFlag_WakeupPIN(PMU , FL_PMU_WKUP4PIN) )
    {    
        FL_PMU_ClearFlag_WakeupPIN(PMU , FL_PMU_WKUP4PIN);
    }   
}
    

// �ⲿ�����жϳ�ʼ��
void WKUP_init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};    
    
    //���ű��ش���ѡ��
    FL_RCC_EnableEXTIOnSleep();//����ʹ���ⲿ�жϲ���
    FL_RCC_EnableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_EXTI);//EXTI����ʱ��ʹ��    
    
    //�õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.pin        = FL_GPIO_PIN_6;
    GPIO_InitStruct.mode       = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull       = DISABLE;
    GPIO_InitStruct.remapPin   = DISABLE;	
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);


    FL_GPIO_SetWakeupInterruptEntry(GPIO, FL_GPIO_WAKEUP_INT_ENTRY_NMI);//NMI�ж����
    FL_GPIO_SetWakeupEdge(GPIO, FL_GPIO_WAKEUP_4, FL_GPIO_WAKEUP_TRIGGER_FALLING);//�½��ػ���
    FL_GPIO_EnableWakeup(GPIO, FL_GPIO_WAKEUP_4);//ʹ��NWKUP����
}
