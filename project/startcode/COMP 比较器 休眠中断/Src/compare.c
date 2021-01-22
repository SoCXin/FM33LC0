#include "user_init.h"
#include "compare.h"

void COMPx_IRQHandler(void)
{
    //ע��������źŵ��˲������������󴥷��ж�
    if(SET == LL_COMP_IsActiveComparator1(COMP_COMMON))
    {
        LL_COMP_ClearFlag_Comparator1(COMP_COMMON);    //���COMP1�жϱ�־
        
        if(SET == LL_COMP_GetComparatorOutput(COMP1))    //�Ƚ���1 V+��ѹ����V-
        {
            LED0_ON();
        }
        else                                //�Ƚ���1 V+��ѹ����V-
        {
            LED0_OFF();
        }    
    }
    
    if(SET == LL_COMP_IsActiveComparator2(COMP_COMMON))
    {
        LL_COMP_ClearFlag_Comparator2(COMP_COMMON);    //���COMP2�жϱ�־
        
        if(SET == LL_COMP_GetComparatorOutput(COMP2))    //�Ƚ���2 V+��ѹ����V-
        {
            LED0_ON();
        }
        else                                //�Ƚ���2 V+��ѹ����V-
        {
            LED0_OFF();
        }
    }
}

//�Ƚ�����������
void COMP_IO_Init(void)
{
LL_GPIO_InitTypeDef    GPIO_InitStruct;

//����û���õ������ţ���ע�͵�
    //COMP1����    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;//COMP1_INP1
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOD,&GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;//COMP1_INP2
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOD,&GPIO_InitStruct);    

    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;//COMP1_INN1
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);

    //COMP1���    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_11;//COMP1_OUT
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOD,&GPIO_InitStruct);        

    //COMP2
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;//COMP2_INN1
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;//COMP2_INN2
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_8;//COMP2_INP1
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_9;//COMP2_INP2
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);    

    //COMP2���    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_12;//COMP2_OUT
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOB,&GPIO_InitStruct);    
}

//�Ƚ���1�Ĵ�����ʼ��
void COMP1_Init(void)
{
LL_COMP_InitTypeDef COMP_InitStruct;
    
    //������ڲ�VREF��1/2VREF�Ƚϡ����VREF��������ż�ȽϾͲ���Ҫ��VREF
    //VREF��VREF_BUFF Լ4uA
    LL_VREF_EnableVREF(VREF);//��1.22V
    LL_OPA_EnableVrefBuffer(OPA1);//ʹ��
    LL_OPA_DisableByPassVrefBuffer(OPA1);//��bypass
    LL_OPA_SetNegtiveInputChannel(OPA1, LL_OPA_NEGTIVE_INPUT_CHANNEL_OPA_VREF);

    COMP_InitStruct.Edge             = LL_COMP_COMPARATOR_INTERRUPT_EDGE_BOTH;//�ж���
    COMP_InitStruct.Polarity         = LL_COMP_COMPARAROT_OUTPUT_POLARITY_NORMAL;//��������
    COMP_InitStruct.NegativeInput    = LL_COMP_COMPARAROT_NEGATIVEVE_INPUT_VREF;//INN
    COMP_InitStruct.PositiveInput    = LL_COMP_COMPARAROT_POSITIVE_INPUT_COMP_INP2;//INP
    COMP_InitStruct.DigitalFilter    = DISABLE;//���˲�
    LL_COMP_Init(COMP1, &COMP_InitStruct);

    LL_COMP_EnableITComper1(COMP_COMMON);//1�������ж�
    /*NVIC�ж�����*/
    NVIC_DisableIRQ(COMPx_IRQn);
    NVIC_SetPriority(COMPx_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(COMPx_IRQn);    
    LL_COMP_Enable(COMP1);//ʹ�ܱȽ���1
}

//�Ƚ���2�Ĵ�����ʼ��
void COMP2_Init(void)
{
LL_COMP_InitTypeDef COMP_InitStruct;
    
    //������ڲ�VREF��1/2VREF�Ƚϡ����VREF��������ż�ȽϾͲ���Ҫ��VREF
    //VREF��VREF_BUFF Լ4uA
    LL_VREF_EnableVREF(VREF);//��1.22V
    LL_OPA_EnableVrefBuffer(OPA1);//ʹ��
    LL_OPA_DisableByPassVrefBuffer(OPA1);//��bypass
    LL_OPA_SetNegtiveInputChannel(OPA2, LL_OPA_NEGTIVE_INPUT_CHANNEL_OPA_VREF);

    COMP_InitStruct.Edge             = LL_COMP_COMPARATOR_INTERRUPT_EDGE_BOTH;//�ж���
    COMP_InitStruct.Polarity         = LL_COMP_COMPARAROT_OUTPUT_POLARITY_NORMAL;//��������
    COMP_InitStruct.NegativeInput    = LL_COMP_COMPARAROT_NEGATIVEVE_INPUT_COMP_INN1;//INN
    COMP_InitStruct.PositiveInput    = LL_COMP_COMPARAROT_POSITIVE_INPUT_COMP_INP1;//INP
    COMP_InitStruct.DigitalFilter    = DISABLE;//���˲�
    LL_COMP_Init(COMP2, &COMP_InitStruct);

    LL_COMP_EnableITComper2(COMP_COMMON);//1�������ж�
    /*NVIC�ж�����*/
    NVIC_DisableIRQ(COMPx_IRQn);
    NVIC_SetPriority(COMPx_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(COMPx_IRQn);        
    LL_COMP_Enable(COMP2);//ʹ�ܱȽ���2
}


