#include "main.h"
#include "aes.h"

void ByteExChange(uint32_t* pWord, uint32_t length)
{
	int32_t i = 0;
	int32_t value = 0;
	uint32_t* pRam = pWord;
	for (i = 0; i < length; i++)
	{
		value = (*pRam << 24) + (((*pRam & 0xFF00) >> 8)<< 16) + (((*pRam & 0xFF0000) >> 16) << 8) + (*pRam >> 24) ;
		*pRam++ = value;
	}
}

/**
  * @brief	����MultH����128bit����H����(h0�����Կ���32bit)
  * @param 	H����	16�ֽڳ��ȵ���Կ  
  * @param 	����	16          
  * @retval	None
  */
void AES_H_WriteEx(uint8_t *hxIn)
{
	uint8_t i;
	__IO uint32_t temp32;

	for (i = 0; i < 16; i = i+4)
	{
		temp32 = (hxIn[0+i] << 24) | (hxIn[1+i] << 16) | (hxIn[2+i] << 8) | hxIn[3+i];
		FL_AES_WriteHParams(AES, (16-i)/4-1, temp32);
	}
	
}

/**
  * @brief	��ȡMultH����128bit����H����(h0�����Կ���32bit)
  * @param 	H����	16�ֽڳ��ȵ���Կ  
  * @param 	����	16          
  * @retval	None
  */
void AES_H_ReadEx(uint8_t *hxOut)
{
	uint8_t i;
	__IO uint32_t temp32;
	for (i = 0; i < 16; i = i+4)
	{
		temp32 = FL_AES_ReadHParams(AES, (16-i)/4-1);
		hxOut[0+i] = temp32 >> 24;
		hxOut[1+i] = temp32 >> 16;
		hxOut[2+i] = temp32 >> 8;
		hxOut[3+i] = temp32;
	}
}


/**
  * @brief	���üӽ�����Կ(key0�����Կ���32bit)
  * @param 	��Կ	16/24/32�ֽڳ��ȵ���Կ  
  * @param 	����	16/24/32          
  * @retval	None
  */
void AES_KEY_WriteEx(uint8_t *keyIn, uint8_t len)
{
	uint8_t i;
	__IO uint32_t temp32;
	
	if ((len != 16) && (len != 24) && (len != 32)) return;
	
	for (i = 0; i < len; i = i+4)
	{
		temp32 = (keyIn[0+i] << 24) | (keyIn[1+i] << 16) | (keyIn[2+i] << 8) | keyIn[3+i];
		FL_AES_WriteKeys(AES, (len-i)/4-1, temp32);
	}
	
}

/**
  * @brief	��ȡ�ӽ�����Կ����һ���ִ����Կ���32bit
  * @param 	��Կ	16/24/32�ֽڳ��ȵ���Կ  
  * @param 	����	16/24/32          
  * @retval	None
  */
void AES_KEY_ReadEx(uint8_t *keyOut, uint8_t len)
{
	uint8_t i;
	__IO uint32_t temp32;
	
	if( (len != 16) && (len != 24) && (len != 32) ) return;
	
	for (i = 0; i < len; i = i+4)
	{
		temp32 = FL_AES_ReadKeys(AES , (len-i)/4-1);
		keyOut[0+i] = temp32 >> 24;
		keyOut[1+i] = temp32 >> 16;
		keyOut[2+i] = temp32 >> 8;
		keyOut[3+i] = temp32;
	}
}

/**
  * @brief	���ó�ʼ����
  * @param 	��ʼ����        
  * @retval	None
  */
void AES_IVR_WriteEx(uint8_t *ivrIn)
{
	uint8_t i;
	__IO uint32_t temp32;
	
	for(i=0; i<4*4; i=i+4)
	{ 
		temp32 = (ivrIn[0+i] << 24) | (ivrIn[1+i] << 16) | (ivrIn[2+i] << 8) | ivrIn[3+i];
		FL_AES_WriteIVR(AES, (16-i)/4-1, temp32);
	}
}

/**
  * @brief	��ȡ��ʼ����
  * @param 	��ʼ����        
  * @retval	None
  */

void AES_IVR_ReadEx(uint8_t *ivrOut)
{
	uint8_t i;
	__IO uint32_t temp32;
	
	for (i = 0; i < 4*4; i = i+4)
	{
		temp32 = FL_AES_ReadIVR(AES, (4*4-i)/4-1);
		ivrOut[0+i] = temp32>>24;
		ivrOut[1+i] = temp32>>16;
		ivrOut[2+i] = temp32>>8;
		ivrOut[3+i] = temp32;	
	}
}

/**
  * @brief	���üӽ������ݣ�16�ֽڣ�128bit��������������
  * @param 	��ʼ����        
  * @retval	None
  */

void AES_DIN_GroupWrite_128BIT(uint8_t *dataIn)
{
	uint8_t i;
	__IO uint32_t temp32;

	for (i = 0; i < 16; i = i+4)
	{
		temp32 = (dataIn[0+i] << 24) | (dataIn[1+i] << 16) | (dataIn[2+i] << 8) | dataIn[3+i];
		FL_AES_WriteInputData(AES, temp32);
	}
}

/**
  * @brief	�ӽ������������16�ֽڣ�128bit�������������        
  * @param 	��ʼ����        
  * @retval	None
  */

void AES_DOUT_GroupRead_128BIT(uint8_t *dataOut)
{
	uint8_t i;
	__IO uint32_t temp32;
	
	for (i = 0; i < 16; i = i+4)
	{
		temp32 = FL_AES_ReadOutputData(AES);
		dataOut[0+i] = temp32 >> 24;
		dataOut[1+i] = temp32 >> 16;
		dataOut[2+i] = temp32 >> 8;
		dataOut[3+i] = temp32;
	}
}

/**
  * @brief	������16�ֽڣ�128bit���������ݣ�Ȼ���ٶ�ȡ16�ֽڣ�128bit����������       
  * @param 	��������   
  * @param 	��������  
  * @retval	None
  */
ErrorStatus AES_GroupWriteAndRead_128BIT(uint8_t *dataIn, uint8_t *dataOut)
{	
	uint16_t i;
	
	/* ����ӽ������� */
	AES_DIN_GroupWrite_128BIT(dataIn);
	
	/* �ȴ�CCF��־����,��ɼ����Լ��Ҫ100��ʱ������ */
	for(i=0;i<500;i++)
	{
		if (SET == FL_AES_IsActiveFlag_Complete(AES)) break;
	}
	/* ��CCF��־ */
	/* ��ȡǰ������� */ 
	FL_AES_ClearFlag_Complete(AES);
	
	/* ��ȡ��� */
	AES_DOUT_GroupRead_128BIT(dataOut);
	
	if (i == 500) return FAIL;
	else return PASS;
}


/**
  * @brief	������16�ֽڣ�128bit���������ݣ�Ȼ���ٶ�ȡ16�ֽڣ�128bit����������       
  * @param 	��������   
  * @param 	��������  
  * @retval	None
  */
ErrorStatus AES_GroupWriteAndRead_128BIT_IVR(uint8_t *dataIn, uint8_t *dataOut)
{	
	uint16_t i;
	
	/* ����ӽ������� */
	AES_DIN_GroupWrite_128BIT(dataIn);
	
	/* �ȴ�CCF��־����,��ɼ����Լ��Ҫ100��ʱ������ */
	for (i = 0; i < 500; i++)
	{
		if (SET == FL_AES_IsActiveFlag_Complete(AES)) break;
	}
	/* ��CCF��־����ȡǰ������� */
	FL_AES_ClearFlag_Complete(AES);
	
	/* ��ȡ��� */
	AES_IVR_ReadEx(dataOut);
	
	if (i == 500) return FAIL;
	else return PASS;
}


/**
  * @brief	AES��ʼ������
	* @param  KeyLenth This parameter can be one of the following values:
  *           @arg @ref FL_AES_KEY_LENGTH_128B
  *           @arg @ref FL_AES_KEY_LENGTH_192B
  *           @arg @ref FL_AES_KEY_LENGTH_256B
	* @param	CipherMode This parameter can be one of the following values:
  *           @arg @ref FL_AES_CIPHER_ECB
  *           @arg @ref FL_AES_CIPHER_CBC
  *           @arg @ref FL_AES_CIPHER_CTR
  *           @arg @ref FL_AES_CIPHER_MULTH			
	* @param	OperationMode This parameter can be one of the following values:
  *           @arg @ref FL_AES_OPERATION_MODE_ENCRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION
  *           @arg @ref FL_AES_OPERATION_MODE_DECRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION	
	* @param	DataType This parameter can be one of the following values:
  *           @arg @ref FL_AES_DATA_TYPE_32B
  *           @arg @ref FL_AES_DATA_TYPE_16B
  *           @arg @ref FL_AES_DATA_TYPE_8B
  *           @arg @ref FL_AES_DATA_TYPE_1B	
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */
ErrorStatus AES_Init(uint32_t KeyLength, uint32_t CipherMode, uint32_t OperationMode, uint32_t DataType)
{
    FL_AES_InitTypeDef AES_InitStructer;
    /********************���ܹ���********************/
    /* ����AESģ�� */
    FL_AES_DeInit();
    /* ���� AES_InitStruct ΪĬ������ */
    FL_AES_StructInit(&AES_InitStructer);
    AES_InitStructer.keyLength      = KeyLength;
    AES_InitStructer.cipherMode    = CipherMode;
    AES_InitStructer.operationMode = OperationMode;
    AES_InitStructer.dataType      = DataType; 
    /* AES_InitStructer��ʼ����Ӧ������ڵ�ַ�ļĴ���ֵ */
    return FL_AES_Init(AES,&AES_InitStructer);
}

/**
  * @brief  AES�ӽ��ܴ�������
  * @note   DataOutָ��ռ��ɵ��������룬�ռ��С������16�ֽڵ�����������Ϊ��ʹ�ǲ���16�ֽڵ����ݽ��м��ܣ�AES������16�ֽڻ���в��������Ȼ���ٽ��мӽ��ܣ�
	* @param    KeyIn ��Կָ��
	* @param    KeyLen ��Կ����
	* @param    IVRIn ����ָ��	
	* @param	DataIn ������������ָ��
	* @param	DataInLen �����������볤��
	* @param	DataOut �����������ָ��
	* @param	DataOutLen �����������
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */

ErrorStatus AES_EncryptionAndDecryption(uint8_t *keyIn, uint8_t keyLen, uint8_t *ivrIn, uint8_t *dataIn, uint32_t dataInLen, uint8_t *dataOut, uint32_t* dataOutLen)
{
    uint32_t i;
	uint32_t result = 0;
	uint8_t tempBuf[16];
	/* ������Կ */
	if (FL_AES_GetCipherMode(AES) != FL_AES_CIPHER_MULTH)
	{
        AES_KEY_WriteEx(keyIn, keyLen);	
	}
	else
	{
		AES_H_WriteEx(keyIn);
	}
	/* CTR��CBCģʽ��дAES_IVRx�Ĵ��� */
	if ((*ivrIn != NULL) && (FL_AES_GetCipherMode(AES) != FL_AES_CIPHER_ECB))
	{
		AES_IVR_WriteEx(ivrIn);	
	}
	/* ����AES */
	FL_AES_Enable(AES);

	for (i = 0; i < dataInLen / 16; i++)
	{
		if (FL_AES_GetCipherMode(AES) == FL_AES_CIPHER_MULTH)
		{
			result = AES_GroupWriteAndRead_128BIT_IVR(dataIn + 16 * i, dataOut + 16 * i);
			if(result == FAIL) return FAIL;
		}
		else
		{
			result = AES_GroupWriteAndRead_128BIT(dataIn + 16 * i, dataOut + 16 * i);
			if(result == FAIL) return FAIL;
		}
	}
	if (dataInLen % 16)
	{
		memset(tempBuf, 0, sizeof(tempBuf));
		memcpy(tempBuf, dataIn + i * 16, dataInLen - i * 16);
		if (FL_AES_GetOperationMode(AES) == FL_AES_CIPHER_MULTH)
		{
			result = AES_GroupWriteAndRead_128BIT_IVR(tempBuf, dataOut + i * 16);
			if (result == FAIL) return FAIL;
		}
		else
		{
			result = AES_GroupWriteAndRead_128BIT(tempBuf, dataOut + i * 16);
			if (result == FAIL) return FAIL;
		}
	}
	if (FL_AES_GetCipherMode(AES) == FL_AES_CIPHER_CTR)
	{
		*dataOutLen = dataInLen;
	}
	else
	{
		*dataOutLen = ((dataInLen + 15) / 16) * 16;
	}
	FL_AES_Disable(AES);
	return PASS;
}





/**
  * @brief	AES��ECBģʽ���Գ���
  * @param	None
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */
ErrorStatus Test_AES_ECB_Encrypt(void)
{
	uint8_t dataInBuf[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t keyBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31};
	uint8_t ivrBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32};
	uint8_t dataOut[16] = {0x00};
	uint32_t dataOutLen;
	const uint8_t scrResultBuf[16] = {0x17, 0x6C, 0xF5, 0x23, 0x86, 0xCD, 0x8A, 0x11, 0x9F, 0x78, 0x15, 0x94, 0x72, 0x38, 0xE3, 0xF5};
	uint32_t result;
    /********************���ܹ���********************/
	AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 10, dataOut, &dataOutLen);
	result = memcmp(dataOut,scrResultBuf, 16);
	if (result != 0) return FAIL;
	return PASS;

}

ErrorStatus Test_AES_ECB_Decrypt(void)
{
	uint8_t dataInBuf[16] = {0x17, 0x6C, 0xF5, 0x23, 0x86, 0xCD, 0x8A, 0x11, 0x9F, 0x78, 0x15, 0x94, 0x72, 0x38, 0xE3, 0xF5};
	uint8_t keyBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31};
	uint8_t ivrBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32};
	uint8_t dataOut[16] = {0x00};
	uint32_t dataOutLen;
	const uint8_t scrResultBuf[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint32_t result;
    /********************���ܹ���********************/
    AES_EncryptionAndDecryption(keyBuf,16,ivrBuf,dataInBuf,16,dataOut,&dataOutLen);
	result = memcmp(dataOut,scrResultBuf,16);
	if (result != 0) return FAIL;
	return PASS;

}

/**
  * @brief	AES��CTRģʽ���Գ���
  * @param	None
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */

ErrorStatus Test_AES_CTR_Encrypt(void)
{
	uint8_t dataInBuf[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t keyBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31};
	uint8_t ivrBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32};
	uint8_t dataOut[16] = {0x00};
	uint32_t dataOutLen;
	const uint8_t scrResultBuf[16] = {0xDC, 0xCA, 0xB2, 0x5E, 0x5C, 0xCA, 0xFA, 0x88, 0xC1, 0x8B, 0xFF, 0x1B, 0x3D, 0xD8, 0x4A, 0x97};
	uint32_t result;
    /********************���ܹ���********************/
	AES_EncryptionAndDecryption(keyBuf,16,ivrBuf,dataInBuf,16,dataOut,&dataOutLen);
	result = memcmp(dataOut,scrResultBuf,16);
	if (result != 0) return FAIL;
	return PASS;

}

/**
  * @brief	AES��CTRģʽ���Գ���
  * @param	None
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */

ErrorStatus Test_AES_CTR_Decrypt(void)
{
	uint8_t dataInBuf[16] = {0xDC, 0xCA, 0xB2, 0x5E, 0x5C, 0xCA, 0xFA, 0x88, 0xC1, 0x8B, 0xFF, 0x1B, 0x3D, 0xD8, 0x4A, 0x97};
	uint8_t keyBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31};
	uint8_t ivrBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32};
	uint8_t dataOut[16] = {0x00};
	uint32_t dataOutLen;
	const uint8_t scrResultBuf[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint32_t result;
    /********************���ܹ���********************/
	AES_EncryptionAndDecryption(keyBuf,16,ivrBuf,dataInBuf,16,dataOut,&dataOutLen);
	result = memcmp(dataOut,scrResultBuf,16);
	if (result != 0) return FAIL;
	return PASS;

}

/**
  * @brief	AES��CBCģʽ���Գ���
  * @param	None
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */

ErrorStatus Test_AES_CBC_Encrypt(void)
{
	uint8_t dataInBuf[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t keyBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31};
	uint8_t ivrBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32};
	uint8_t dataOut[16] = {0x00};
	uint32_t dataOutLen;
	const uint8_t scrResultBuf[16] = {0x62, 0xAA, 0xA1, 0x85, 0xEC, 0xFB, 0x83, 0x39, 0xAB, 0x9E, 0x11, 0x7A, 0xAA, 0xFD, 0x79, 0x68};
	uint32_t result;
    /********************���ܹ���********************/
	AES_EncryptionAndDecryption(keyBuf,16,ivrBuf,dataInBuf,16,dataOut,&dataOutLen);
	result = memcmp(dataOut,scrResultBuf,16);
	if (result != 0) return FAIL;
	return PASS;

}

/**
  * @brief	AES��CBCģʽ���Գ���
  * @param	None
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */

ErrorStatus Test_AES_CBC_Decrypt(void)
{
	uint8_t dataInBuf[16] = {0x62, 0xAA, 0xA1, 0x85, 0xEC, 0xFB, 0x83, 0x39, 0xAB, 0x9E, 0x11, 0x7A, 0xAA, 0xFD, 0x79, 0x68};
	uint8_t keyBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31};
	uint8_t ivrBuf[16] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32};
	uint8_t dataOut[16] = {0x00};
	uint32_t dataOutLen;
	const uint8_t scrResultBuf[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint32_t result;
	/********************���ܹ���********************/
	AES_EncryptionAndDecryption(keyBuf,16,ivrBuf,dataInBuf,16,dataOut,&dataOutLen);
	result = memcmp(dataOut,scrResultBuf,16);
	if (result != 0) return FAIL;
	return PASS;
}


/**
  * @brief	AES��MULTHģʽ���Գ���
  * @param	None
	* @Note		MULTHģʽ�£���������DataType���ѡ��FL_AES_IVR_SWAP_32B
  * @retval	���ش���״̬������ֵ��
  *       	-PASS ���Գɹ�
  *       	-FAIL ����ʧ��
  */

ErrorStatus Test_AES_MULTH(void)
{
	uint32_t dataInBuf[40] = {
        0xb41daef8,0xe7d02b66,0x9061a816,0x6a317b9e,
        0x434cbdba,0x78fe5268,0x0dd73ba7,0x3cd2e070,
        0x4ba4511b,0x58ea7aa3,0xc87b8419,0xa98756bf,
        0x4c217832,0xa58a98ca,0x5ca90d2d,0x56c29ea1,
        0xa4a583e6,0x109e5b42,0x86f49998,0x42b1c6cf,
        0x61c9895b,0x5d5cc16e,0x65adc8bb,0x7d7ec242,
        0x817fad74,0x3ebea341,0x143ae52c,0x7aa6aa83,
        0x8b6bae55,0x60a85675,0x322e7b50,0x95ad2998,
        0x7f3890ad,0x6719d313,0xab975a8a,0x2aaec3e3,
        0x30549636,0x2c2ab020,0xc1a7c503,0xb8db2fb0,
	};
	uint32_t hbuf[4] = {
        0xa7121942,0x8e9a431a,0x87deb4ab,0x9cea030e
	};

	uint32_t ivrBuf[4] = {
        0x7c776dd9,0x444bccc4,0xc9367885,0x4be99b67
	};
	
	uint32_t scrResultBuf[40] = {
		0xc26d7314,0x7ef12993,0x7924d021,0x49a288bd,
        0xb8074a26,0x6080b4ef,0x9dd6f65c,0xa1316074,
        0xe64ce340,0x69d9e114,0x22f96a6f,0xa9e6b908,
        0x0bfe4c53,0x87ebab8a,0x3caf1e52,0x6c7779e0,
        0xb0ad8400,0x174fe560,0x052640e8,0x67ad35a1,
        0x35478633,0x03653c71,0x1fcec3e7,0x047e32cd,
        0x3cb75b8e,0x9102fcc4,0xfdc594e5,0xc7f52620,
        0x674bd35d,0x6ea2885f,0x70efa246,0x4304712d,
        0x1a1a0bb7,0xadff3ae5,0x7ce6ae15,0xaaf7e174,
        0xd0287e4d,0x531de812,0x22ab2933,0x50173ddb,
	};
	
	uint32_t dataOut[40];
	uint32_t dataOutLen;
	uint32_t result;
    
	ByteExChange(dataInBuf,40);
	ByteExChange(hbuf,4);
	ByteExChange(ivrBuf,4);
	ByteExChange(scrResultBuf,40);

	AES_EncryptionAndDecryption((uint8_t*)hbuf,16,(uint8_t*)ivrBuf,(uint8_t*)dataInBuf,40*4,(uint8_t*)dataOut,&dataOutLen);
	result = memcmp(dataOut,scrResultBuf,40*4);
	if (result != 0) return FAIL;
	return PASS;

}

