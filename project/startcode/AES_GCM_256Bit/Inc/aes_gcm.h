
#ifndef __AES_GCM_H
#define __AES_GCM_H
#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33xx.h"
	
ErrorStatus Test_AES_IV_96Bit_GCM128Bit(void);
ErrorStatus Test_AES_IV_Not96Bit_GCM128Bit(void);
ErrorStatus Test_AES_IV_96Bit_GCM256Bit(void);
ErrorStatus Test_AES_IV_96Bit_GCM192Bit(void);
#ifdef __cplusplus
}
#endif

#endif /* __AES_GCM_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
