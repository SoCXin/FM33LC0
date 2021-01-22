#include "user_init.h"
#include "main.h"
#include "gpio_interrupt.h"

//引脚中断
void GPIO_IRQHandler(void)
{  
    if(FL_GPIO_IsActiveFlag_EXTI(GPIO,FL_GPIO_EXTI_LINE_9))
    {
        FL_GPIO_ClearFlag_EXTI(GPIO,FL_GPIO_EXTI_LINE_9);					
    }
}
    

// 外部引脚中断初始化
void GPIO_interrupt_init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};    
    
    //引脚边沿触发选择
    FL_RCC_EnableEXTIOnSleep();//休眠使能外部中断采样
    FL_RCC_EnableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_EXTI);//EXTI工作时钟使能    
    
    //用到的GPIO引脚    设为输入 
    GPIO_InitStruct.pin        = FL_GPIO_PIN_6;
    GPIO_InitStruct.mode       = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull       = DISABLE;
    GPIO_InitStruct.remapPin   = DISABLE;	
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);


    FL_GPIO_SetTriggerEdge(GPIO,FL_GPIO_EXTI_LINE_9,FL_GPIO_EXTI_TRIGGER_EDGE_DISABLE);//关闭边沿触发
    //每条LINE 只能选一个引脚 
    FL_GPIO_SetExtiLine9(GPIO,FL_GPIO_EXTI_LINE_9_PC6);//中断引脚选择
    FL_GPIO_EnableDigitalFilter(GPIO, FL_GPIO_EXTI_LINE_9);//EXTI数字滤波功能
    FL_GPIO_SetTriggerEdge(GPIO,FL_GPIO_EXTI_LINE_9,FL_GPIO_EXTI_TRIGGER_EDGE_FALLING);//边沿选择    
    FL_GPIO_ClearFlag_EXTI(GPIO,FL_GPIO_EXTI_LINE_9);	//清除中断标志
    
    
    /*NVIC中断配置*/
    NVIC_DisableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn,2);//中断优先级配置
    NVIC_EnableIRQ(GPIO_IRQn);
}
