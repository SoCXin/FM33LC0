#include "lptim32_timing.h"

void LPTIM32_Timing_Start()
{
    //使能LPTIM32
    FL_LPTIM32_Enable(LPTIM32);
}

void LPTIM32_Timing_Loop()
{
    
}

void LPTIM_IRQHandler()
{
    if(FL_LPTIM32_IsEnabledIT_Update(LPTIM32) && FL_LPTIM32_IsActiveFlag_Update(LPTIM32))
    {
        FL_LPTIM32_ClearFlag_Update(LPTIM32);
    }
}
