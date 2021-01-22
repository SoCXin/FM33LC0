#include "user_init.h"
#include "main.h"
#include "gpio_interrupt.h"

//�����ж�
void GPIO_IRQHandler(void)
{
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_0))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_0);
        if(LINE_0_N){}//IO�ڵ͵�ƽ
        if(LINE_0_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_1))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_1);
        if(LINE_1_N){}//IO�ڵ͵�ƽ
        if(LINE_1_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_2))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_2);
        if(LINE_2_N){}//IO�ڵ͵�ƽ
        if(LINE_2_P){}//IO�ڸߵ�ƽ
    }    
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_3))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_3);
        if(LINE_3_N){}//IO�ڵ͵�ƽ
        if(LINE_3_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_4))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_4);
        if(LINE_4_N){}//IO�ڵ͵�ƽ
        if(LINE_4_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_5))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_5);
        if(LINE_5_N){}//IO�ڵ͵�ƽ
        if(LINE_5_P){}//IO�ڸߵ�ƽ
    }    
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_6))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_6);
        if(LINE_6_N){}//IO�ڵ͵�ƽ
        if(LINE_6_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_7))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_7);
        if(LINE_7_N){}//IO�ڵ͵�ƽ
        if(LINE_7_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_8))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_8);
        if(LINE_8_N){}//IO�ڵ͵�ƽ
        if(LINE_8_P){}//IO�ڸߵ�ƽ
    }    
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);
        if(LINE_9_N){}//IO�ڵ͵�ƽ
        if(LINE_9_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_10))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_10);
        if(LINE_10_N){}//IO�ڵ͵�ƽ
        if(LINE_10_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_11))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_11);
        if(LINE_11_N){}//IO�ڵ͵�ƽ
        if(LINE_11_P){}//IO�ڸߵ�ƽ
    }    
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_12))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_12);
        if(LINE_12_N){}//IO�ڵ͵�ƽ
        if(LINE_12_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_13))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_13);
        if(LINE_13_N){}//IO�ڵ͵�ƽ
        if(LINE_13_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_14))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_14);
        if(LINE_14_N){}//IO�ڵ͵�ƽ
        if(LINE_14_P){}//IO�ڸߵ�ƽ
    }
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_15))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_15);
        if(LINE_15_N){}//IO�ڵ͵�ƽ
        if(LINE_15_P){}//IO�ڸߵ�ƽ
    }    
}
    

// �ⲿ�����жϳ�ʼ��
void GPIO_interrupt_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};    
    
    //���ű��ش���ѡ��
    LL_RCC_Enable_SleepmodeExternalInterrupt();//����ʹ���ⲿ�жϲ���
    LL_RCC_SetEXTIClockSource(LL_RCC_EXTERNAL_INTERRUPT_SAMPLING_CLOCK_SELECT_LSCLK);//EXTI�жϲ���ʱ��ѡ��
    LL_RCC_Group1_EnableOperationClock(LL_RCC_OPERATION1_CLOCK_EXTI);//EXTI����ʱ��ʹ��    
    
    //LINE_0   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_0_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_0_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_0, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine0(GPIO_COMMON, LL_GPIO_EXTI_LINE_0_PA0);//�ж�����ѡ��
//    LL_GPIO_SetExitLine0(GPIO_COMMON, LL_GPIO_EXTI_LINE_0_PA1);//�ж�����ѡ��
//    LL_GPIO_SetExitLine0(GPIO_COMMON, LL_GPIO_EXTI_LINE_0_PA2);//�ж�����ѡ��
//    LL_GPIO_SetExitLine0(GPIO_COMMON, LL_GPIO_EXTI_LINE_0_PA3);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_0);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_0, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_0);//����жϱ�־
    
    //LINE_1   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_1_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_1_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_1, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine1(GPIO_COMMON, LL_GPIO_EXTI_LINE_1_PA4);//�ж�����ѡ��
//    LL_GPIO_SetExitLine1(GPIO_COMMON, LL_GPIO_EXTI_LINE_1_PA5);//�ж�����ѡ��
//    LL_GPIO_SetExitLine1(GPIO_COMMON, LL_GPIO_EXTI_LINE_1_PA6);//�ж�����ѡ��
//    LL_GPIO_SetExitLine1(GPIO_COMMON, LL_GPIO_EXTI_LINE_1_PA7);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_1);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_1, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_1);//����жϱ�־
    
    //LINE_2   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_2_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_2_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_2, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine2(GPIO_COMMON, LL_GPIO_EXTI_LINE_2_PA8);//�ж�����ѡ��
//    LL_GPIO_SetExitLine2(GPIO_COMMON, LL_GPIO_EXTI_LINE_2_PA9);//�ж�����ѡ��
//    LL_GPIO_SetExitLine2(GPIO_COMMON, LL_GPIO_EXTI_LINE_2_PA10);//�ж�����ѡ��
//    LL_GPIO_SetExitLine2(GPIO_COMMON, LL_GPIO_EXTI_LINE_2_PA11);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_2);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_2, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_2);//����жϱ�־    


    //LINE_3   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_3_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_3_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_3, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine3(GPIO_COMMON, LL_GPIO_EXTI_LINE_3_PA12);//�ж�����ѡ��
//    LL_GPIO_SetExitLine3(GPIO_COMMON, LL_GPIO_EXTI_LINE_3_PA13);//�ж�����ѡ��
//    LL_GPIO_SetExitLine3(GPIO_COMMON, LL_GPIO_EXTI_LINE_3_PA14);//�ж�����ѡ��
//    LL_GPIO_SetExitLine3(GPIO_COMMON, LL_GPIO_EXTI_LINE_3_PA15);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_3);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_3, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_3);//����жϱ�־

    //LINE_4   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_4_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_4_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_4, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine4(GPIO_COMMON, LL_GPIO_EXTI_LINE_4_PB0);//�ж�����ѡ�񣨴�usb�汾оƬû�У�
//    LL_GPIO_SetExitLine4(GPIO_COMMON, LL_GPIO_EXTI_LINE_4_PB1);//�ж�����ѡ�񣨴�usb�汾оƬû�У�
    LL_GPIO_SetExitLine4(GPIO_COMMON, LL_GPIO_EXTI_LINE_4_PB2);//�ж�����ѡ��
//    LL_GPIO_SetExitLine4(GPIO_COMMON, LL_GPIO_EXTI_LINE_4_PB3);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_4);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_4, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_4);//����жϱ�־
    
    //LINE_5   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_5_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_5_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_5, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine5(GPIO_COMMON, LL_GPIO_EXTI_LINE_5_PB4);//�ж�����ѡ��
//    LL_GPIO_SetExitLine5(GPIO_COMMON, LL_GPIO_EXTI_LINE_5_PB5);//�ж�����ѡ��
//    LL_GPIO_SetExitLine5(GPIO_COMMON, LL_GPIO_EXTI_LINE_5_PB6);//�ж�����ѡ��
    LL_GPIO_SetExitLine5(GPIO_COMMON, LL_GPIO_EXTI_LINE_5_PB7);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_5);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_5, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_5);//����жϱ�־

    //LINE_6   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_6_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_6_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_6, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine6(GPIO_COMMON, LL_GPIO_EXTI_LINE_6_PB8);//�ж�����ѡ��
//    LL_GPIO_SetExitLine6(GPIO_COMMON, LL_GPIO_EXTI_LINE_6_PB9);//�ж�����ѡ��
//    LL_GPIO_SetExitLine6(GPIO_COMMON, LL_GPIO_EXTI_LINE_6_PB10);//�ж�����ѡ��
    LL_GPIO_SetExitLine6(GPIO_COMMON, LL_GPIO_EXTI_LINE_6_PB11);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_6);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_6, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_6);//����жϱ�־
    
    //LINE_7   �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_7_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_7_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_7, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine7(GPIO_COMMON, LL_GPIO_EXTI_LINE_7_PB12);//�ж�����ѡ��
//    LL_GPIO_SetExitLine7(GPIO_COMMON, LL_GPIO_EXTI_LINE_7_PB13);//�ж�����ѡ��
//    LL_GPIO_SetExitLine7(GPIO_COMMON, LL_GPIO_EXTI_LINE_7_PB14);//�ж�����ѡ��
//    LL_GPIO_SetExitLine7(GPIO_COMMON, LL_GPIO_EXTI_LINE_7_PB15);//�ж�����ѡ�񣨴�usb�汾оƬû�У�    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_7);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_7, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_7);//����жϱ�־    


    //LINE_8  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_8_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_8_GPIO, &GPIO_InitStruct);
    
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_8, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine8(GPIO_COMMON, LL_GPIO_EXTI_LINE_8_PC0);//�ж�����ѡ��
//    LL_GPIO_SetExitLine8(GPIO_COMMON, LL_GPIO_EXTI_LINE_8_PC1);//�ж�����ѡ��
//    LL_GPIO_SetExitLine8(GPIO_COMMON, LL_GPIO_EXTI_LINE_8_PC2);//�ж�����ѡ��
    LL_GPIO_SetExitLine8(GPIO_COMMON, LL_GPIO_EXTI_LINE_8_PC3);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_8);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_8, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_8);//����жϱ�־    
    
    //LINE_9  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_9_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_9_GPIO, &GPIO_InitStruct);

    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_9, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine9(GPIO_COMMON, LL_GPIO_EXTI_LINE_9_PC4);//�ж�����ѡ��
//    LL_GPIO_SetExitLine9(GPIO_COMMON, LL_GPIO_EXTI_LINE_9_PC5);//�ж�����ѡ��
//    LL_GPIO_SetExitLine9(GPIO_COMMON, LL_GPIO_EXTI_LINE_9_PC6);//�ж�����ѡ��
    LL_GPIO_SetExitLine9(GPIO_COMMON, LL_GPIO_EXTI_LINE_9_PC7);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_9, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);//����жϱ�־    

    //LINE_10  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_10_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_10_GPIO, &GPIO_InitStruct);
    
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_10, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine10(GPIO_COMMON, LL_GPIO_EXTI_LINE_10_PC8);//�ж�����ѡ��
//    LL_GPIO_SetExitLine10(GPIO_COMMON, LL_GPIO_EXTI_LINE_10_PC9);//�ж�����ѡ��
//    LL_GPIO_SetExitLine10(GPIO_COMMON, LL_GPIO_EXTI_LINE_10_PC10);//�ж�����ѡ��
    LL_GPIO_SetExitLine10(GPIO_COMMON, LL_GPIO_EXTI_LINE_10_PC11);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_10);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_10, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_10);//����жϱ�־    
    
    //LINE_11  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_11_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_11_GPIO, &GPIO_InitStruct);

    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_11, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_11);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_11, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_11);//����жϱ�־        

    //LINE_12  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_12_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_12_GPIO, &GPIO_InitStruct);
    
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_12, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine12(GPIO_COMMON, LL_GPIO_EXTI_LINE_12_PD0);//�ж�����ѡ��
//    LL_GPIO_SetExitLine12(GPIO_COMMON, LL_GPIO_EXTI_LINE_12_PD1);//�ж�����ѡ��
//    LL_GPIO_SetExitLine12(GPIO_COMMON, LL_GPIO_EXTI_LINE_12_PD2);//�ж�����ѡ��
    LL_GPIO_SetExitLine12(GPIO_COMMON, LL_GPIO_EXTI_LINE_12_PD3);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_12);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_12, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_12);//����жϱ�־    
    
    //LINE_13  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_13_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_13_GPIO, &GPIO_InitStruct);
    
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_13, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine13(GPIO_COMMON, LL_GPIO_EXTI_LINE_13_PD4);//�ж�����ѡ��
//    LL_GPIO_SetExitLine13(GPIO_COMMON, LL_GPIO_EXTI_LINE_13_PD5);//�ж�����ѡ��
//    LL_GPIO_SetExitLine13(GPIO_COMMON, LL_GPIO_EXTI_LINE_13_PD6);//�ж�����ѡ��
//    LL_GPIO_SetExitLine13(GPIO_COMMON, LL_GPIO_EXTI_LINE_13_PD7);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_13);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_13, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_13);//����жϱ�־    
    
    //LINE_14  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_14_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_14_GPIO, &GPIO_InitStruct);
    
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_14, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
//    LL_GPIO_SetExitLine14(GPIO_COMMON, LL_GPIO_EXTI_LINE_14_PD8);//�ж�����ѡ��
//    LL_GPIO_SetExitLine14(GPIO_COMMON, LL_GPIO_EXTI_LINE_14_PD9);//�ж�����ѡ��XTLF���ţ��ر�XTLF��
    LL_GPIO_SetExitLine14(GPIO_COMMON, LL_GPIO_EXTI_LINE_14_PD10);//�ж�����ѡ��XTLF���ţ��ر�XTLF��
//    LL_GPIO_SetExitLine14(GPIO_COMMON, LL_GPIO_EXTI_LINE_14_PD11);//�ж�����ѡ��    
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_14);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_14, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_14);//����жϱ�־    

    //LINE_15  �õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_15_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = ENABLE;
    LL_GPIO_Init(LINE_15_GPIO, &GPIO_InitStruct);
    //����usb�汾оƬû�У�    
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_15, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_15);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_15, LL_GPIO_EXTI_TRIGGER_BOTHEDGE);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_15);//����жϱ�־    
    
    /*NVIC�ж�����*/
    NVIC_DisableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(GPIO_IRQn);
}
