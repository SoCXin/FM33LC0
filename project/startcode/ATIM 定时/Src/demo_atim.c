#include "demo_atim.h"

void ATIM_Start()
{
    //使能LATIM
    FL_ATIM_Enable(ATIM);
}


void ATIM_IRQHandler()
{
    if(FL_ATIM_IsEnabledIT_Update(ATIM) && FL_ATIM_IsActiveFlag_Update(ATIM))
    {
        FL_ATIM_ClearFlag_Update(ATIM);

        //处理更新事件
        //...
    }
}
