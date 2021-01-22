#include "bstim32_timing.h"

void BSTIM32_Start()
{
    //使能BSTIM32
    FL_BSTIM32_Enable(BSTIM32);
}

void BSTIM32_Loop()
{
  
}

void BSTIM_IRQHandler()
{
    if(FL_BSTIM32_IsEnabledIT_Update(BSTIM32) && FL_BSTIM32_IsActiveFlag_Update(BSTIM32))
    {
        FL_BSTIM32_ClearFlag_Update(BSTIM32);

        // 处理更新事件
        // ...
    }
}

void TimeStart(void)
{
    BSTIM32->CNT = 0;
}

uint32_t TimeStop(void)
{
    return BSTIM32->CNT;
}
