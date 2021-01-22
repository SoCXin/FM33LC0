#include "demo_gptim.h"

void GPTIM_Start()
{
    //使能LGPTIM
    FL_GPTIM_Enable(GPTIM0);
}


void GPTIM0_IRQHandler()
{
    if(FL_GPTIM_IsEnabledIT_Update(GPTIM0) && FL_GPTIM_IsActiveFlag_Update(GPTIM0))
    {
        FL_GPTIM_ClearFlag_Update(GPTIM0);

        //处理更新事件
        //...
    }
}

