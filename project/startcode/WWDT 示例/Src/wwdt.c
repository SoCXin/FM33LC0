#include "main.h"
/* WWDT��ʼ�� */
ErrorStatus WWDT_Init(void)
{
	LL_WWDT_InitTypeDef WWDT_InitStruct;
	/* ����������� */
	WWDT_InitStruct.OverflowPeriod = LL_WWDT_OVERFLOW_PERIOD_X1024;
 
	NVIC_DisableIRQ(WWDT_IRQn);
	NVIC_SetPriority(WWDT_IRQn,2);
	NVIC_EnableIRQ(WWDT_IRQn);

  LL_WWDT_ClearFlag_Interrupt(WWDT);	
	/* ���ж� */
	LL_WWDT_EnableIT_WWDT_Interrupt(WWDT);
  
	return LL_WWDT_Init(WWDT, &WWDT_InitStruct);
}

ErrorStatus Test_WWDT(void)
{
	return WWDT_Init();
}

void WWDT_IRQHandler(void)
{

	LL_WWDT_ClearFlag_Interrupt(WWDT);
	LL_WWDT_ResetCounter(WWDT);
}
