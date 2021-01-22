#include "main.h"
/* HDIV≥ı ºªØ */
ErrorStatus DIVAS_Init(void)
{
	return FL_DIVAS_Init(DIV);
}

ErrorStatus Test_DIVAS_Hdiv(void)
{
	int32_t DivisorEnd = 5;
	int16_t Divisor = 2;
	int32_t Quotient;
	int16_t Residue;
	uint32_t result = 0;
	DIVAS_Init();
	result = FL_DIVAS_Hdiv_Calculation(DIV,DivisorEnd,Divisor,&Quotient, &Residue);
	if(result == 0)
	{
		if((Quotient == (DivisorEnd/Divisor)) && (Residue == (DivisorEnd%Divisor)))
			return PASS;
	}
	return FAIL;
}



