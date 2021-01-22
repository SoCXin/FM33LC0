
#ifndef __DIVAS_H
#define __DIVAS_H
#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33xx.h"
	
ErrorStatus DIVAS_Init(void);
ErrorStatus Test_DIVAS_Hdiv(void);
ErrorStatus Test_DIVAS_Root(void);

#ifdef __cplusplus
}
#endif

#endif /* __DIVAS_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
