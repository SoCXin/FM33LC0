#include "user_init.h"
#include "main.h"
#include "gpio_interrupt.h"

//�����ж�
void GPIO_IRQHandler(void)
{  
    if(FL_GPIO_IsActiveFlag_EXTI(GPIO,FL_GPIO_EXTI_LINE_9))
    {
        FL_GPIO_ClearFlag_EXTI(GPIO,FL_GPIO_EXTI_LINE_9);					
    }
}
    

// �ⲿ�����жϳ�ʼ��
void GPIO_interrupt_init(void)
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


    FL_GPIO_SetTriggerEdge(GPIO,FL_GPIO_EXTI_LINE_9,FL_GPIO_EXTI_TRIGGER_EDGE_DISABLE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    FL_GPIO_SetExtiLine9(GPIO,FL_GPIO_EXTI_LINE_9_PC6);//�ж�����ѡ��
    FL_GPIO_EnableDigitalFilter(GPIO, FL_GPIO_EXTI_LINE_9);//EXTI�����˲�����
    FL_GPIO_SetTriggerEdge(GPIO,FL_GPIO_EXTI_LINE_9,FL_GPIO_EXTI_TRIGGER_EDGE_FALLING);//����ѡ��    
    FL_GPIO_ClearFlag_EXTI(GPIO,FL_GPIO_EXTI_LINE_9);	//����жϱ�־
    
    
    /*NVIC�ж�����*/
    NVIC_DisableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(GPIO_IRQn);
}
