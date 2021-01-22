#include "demo_gptim.h"


// 捕获状态
static uint8_t captureStatus = 0;

// 触发捕获前定时器溢出的次数
static uint32_t captureOverflowCount = 0;

uint32_t  capturedValue;


void GPTIM_Start()
{
    //使能ATIM
    FL_GPTIM_Enable(GPTIM0);
}
//PWM输入捕捉
void GPTIM_Loop()
{


    /* 循环调用，当触发捕获时记录捕获值并重新开始捕获 */
    if(captureStatus)
    {
        // 实际捕获值 = 定时器捕获期间溢出次数 * 定时周期 + 当前捕获值
        capturedValue = captureOverflowCount * FL_GPTIM_ReadAutoReload(GPTIM0) + FL_GPTIM_ReadCompareCH1(GPTIM0);
        
        // 处理数据
        // ...

        // 重新开始捕获
        captureStatus = 0;
        FL_GPTIM_Enable(GPTIM0);
    }

 
}

void LPTIM_IRQHandler()
{
    if(FL_GPTIM_IsEnabledIT_Update(GPTIM0) && FL_GPTIM_IsActiveFlag_Update(GPTIM0))
    {
        FL_GPTIM_ClearFlag_Update(GPTIM0);

        // 处理更新事件
        captureOverflowCount++;
        // ...
    }

    if(FL_GPTIM_IsEnabledIT_CC(GPTIM0, FL_GPTIM_CHANNEL_1) && FL_GPTIM_IsActiveFlag_CC(GPTIM0, FL_GPTIM_CHANNEL_1))
    {
        FL_GPTIM_ClearFlag_CC(GPTIM0, FL_GPTIM_CHANNEL_1);

        // 停止捕获
        FL_GPTIM_Disable(GPTIM0);

        // 处理捕获事件
        captureStatus = 1;
        // ...
    }    
}




