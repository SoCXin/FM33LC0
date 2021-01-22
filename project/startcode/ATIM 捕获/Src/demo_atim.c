#include "demo_atim.h"


uint32_t  capturedValue1;
uint32_t  capturedValue2;

void ATIM_Start()
{
    //使能ATIM
    FL_ATIM_Enable(ATIM);
}
//PWM输入捕捉
void ATIM_Loop()
{


        // 实际捕获值
        capturedValue1 = FL_ATIM_ReadCompareCH1(ATIM);
		capturedValue2 = FL_ATIM_ReadCompareCH2(ATIM);
		
        
        // 处理数据
        // ...

 
}


