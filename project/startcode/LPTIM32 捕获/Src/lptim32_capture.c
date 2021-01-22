#include "lptim32_capture.h"

// 捕获状态
static uint8_t captureStatus = 0;

// 捕获状态
static uint8_t capturedValue = 0;

void LPTIM32_Capture_Start()
{
    //使能LPTIM32
    FL_LPTIM32_Enable(LPTIM32);
}

void LPTIM32_Capture_Loop()
{
    /* 循环调用，当触发捕获时记录捕获值并重新开始捕获 */
    if(captureStatus)
    {
        // 实际捕获值 = 定时器捕获期间溢出次数 * 定时周期 + 当前捕获值
        capturedValue = FL_LPTIM32_ReadCompareCH1(LPTIM32);

        // 处理数据
        // ...
        (void)capturedValue;

        // 重新开始捕获
        captureStatus = 0;
        LPTIM32->CNT = 0;
        FL_LPTIM32_Enable(LPTIM32);
    }
}

void LPTIM_IRQHandler()
{
    if(FL_LPTIM32_IsEnabledIT_CC(LPTIM32, FL_LPTIM32_CHANNEL_1) && FL_LPTIM32_IsActiveFlag_CC(LPTIM32, FL_LPTIM32_CHANNEL_1))
    {
        FL_LPTIM32_ClearFlag_CC(LPTIM32, FL_LPTIM32_CHANNEL_1);

        // 停止捕获
        FL_LPTIM32_Disable(LPTIM32);

        // 处理捕获事件
        captureStatus = 1;
        // ...
    }    
}
