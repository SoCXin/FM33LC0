#include "main.h"
/* IWDT��ʼ�� */
ErrorStatus IWDT_Init(void)
{
	LL_IWDT_InitTypeDef IWDT_InitStruct;
	/* Ĭ�ϲ�ʹ�ô��� */
	IWDT_InitStruct.IwdtWindows    = 0;
	/*����ʱ��*/
	IWDT_InitStruct.OverflowPeriod = LL_IWDT_IWDT_OVERFLOW_PERIOD_8000MS;
	return LL_IWDT_Init(IWDT, &IWDT_InitStruct);
}

ErrorStatus Test_IWDT(void)
{
	return IWDT_Init();
}

void IWDT_Clr(void)
{
  LL_IWDG_ReloadCounter(IWDT);
}
