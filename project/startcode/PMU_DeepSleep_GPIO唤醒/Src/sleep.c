#include "sleep.h"
#include "main.h"

// Sleep
void Sleep(void)
{   
    FL_RCC_RCMF_Disable();               //关闭RCMF
    FL_RMU_PDR_Enable(RMU);  			 //打开PDR
    FL_RMU_BORPowerDown_Disable(RMU);  	 //关闭BOR 2uA
    
    /*使用ADC时ADCMonitor功能以及Vref需同时开始，同时关闭*/
    FL_VREF_Disable(VREF);               //关闭VREF1p2
    FL_SVD_DisableADCMonitor(SVD);       //关闭ADC电源检测
    FL_ADC_Disable(ADC);                 //关闭ADC使能
    
    FL_PMU_SetLowPowerMode(PMU,FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP);	
    __WFI();     
}


