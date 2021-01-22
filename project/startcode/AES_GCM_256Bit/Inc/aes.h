#ifndef __AES_H
#define __AES_H
#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33xx.h"
	
ErrorStatus Test_AES_ECB_Encrypt(void);
ErrorStatus Test_AES_ECB_Decrypt(void);
ErrorStatus Test_AES_CTR_Encrypt(void);
ErrorStatus Test_AES_CTR_Decrypt(void);
ErrorStatus Test_AES_CBC_Encrypt(void);
ErrorStatus Test_AES_CBC_Decrypt(void);
ErrorStatus Test_AES_MULTH(void);	
void ByteExChange(uint32_t* pWord, uint32_t Length);
void AES_H_WriteEx(uint8_t *HxIn);
void AES_H_ReadEx(uint8_t *HxOut);
void AES_KEY_WriteEx(uint8_t *KeyIn, uint8_t Len);
void AES_KEY_ReadEx(uint8_t *KeyOut, uint8_t Len);
void AES_IVR_WriteEx(uint8_t *IVRIn);
void AES_IVR_ReadEx(uint8_t *IVROut);
void AES_DIN_GroupWrite_128BIT(uint8_t *DataIn);
void AES_DOUT_GroupRead_128BIT(uint8_t *DataOut);
ErrorStatus AES_GroupWriteAndRead_128BIT(uint8_t *DataIn, uint8_t *DataOut);
ErrorStatus AES_GroupWriteAndRead_128BIT_IVR(uint8_t *DataIn, uint8_t *DataOut);
ErrorStatus AES_Init(uint32_t KeyLenth, uint32_t CipherMode, uint32_t OperationMode, uint32_t DataType);
ErrorStatus AES_EncryptionAndDecryption(uint8_t *KeyIn, uint8_t KeyLen, uint8_t *IVRIn, uint8_t *DataIn, uint32_t DataInLen, uint8_t *DataOut, uint32_t* DataOutLen);
#ifdef __cplusplus
}
#endif

#endif /* __AES_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
