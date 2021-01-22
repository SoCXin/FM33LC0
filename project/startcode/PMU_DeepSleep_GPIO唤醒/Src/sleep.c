#include "sleep.h"
#include "main.h"

// Sleep
void Sleep(void)
{   
    FL_RCC_RCMF_Disable();               //�ر�RCMF
    FL_RMU_PDR_Enable(RMU);  			 //��PDR
    FL_RMU_BORPowerDown_Disable(RMU);  	 //�ر�BOR 2uA
    
    /*ʹ��ADCʱADCMonitor�����Լ�Vref��ͬʱ��ʼ��ͬʱ�ر�*/
    FL_VREF_Disable(VREF);               //�ر�VREF1p2
    FL_SVD_DisableADCMonitor(SVD);       //�ر�ADC��Դ���
    FL_ADC_Disable(ADC);                 //�ر�ADCʹ��
    
    FL_PMU_SetLowPowerMode(PMU,FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP);	
    __WFI();     
}


