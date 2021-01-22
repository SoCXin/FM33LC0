#include "demo_atim.h"

void ATIM_Start()
{
    //使能ATIM
    FL_ATIM_Enable(ATIM);
	//主控输出使能
	 FL_ATIM_EnableALLOutput(ATIM);
}

