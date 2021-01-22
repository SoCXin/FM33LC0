#include "main.h"
#include "aes.h"

typedef enum {
	ENCRYPT,
	DECRYPT
}CRYPT;
	

__STATIC_INLINE void int2Byte_MSB(uint32_t datatemp, uint8_t*buf)
{
    buf[3] = datatemp;
    buf[2] = (datatemp >> 8);
    buf[1] = (datatemp >> 16);
    buf[0] = (datatemp >> 24);
}

static uint32_t revBits( uint32_t n )
{
	n = ((n >> 1 ) & 0x55555555) | ((n << 1 ) & 0xaaaaaaaa);
	n = ((n >> 2 ) & 0x33333333) | ((n << 2 ) & 0xcccccccc);
	n = ((n >> 4 ) & 0x0f0f0f0f) | ((n << 4 ) & 0xf0f0f0f0);
	n = ((n >> 8 ) & 0x00ff00ff) | ((n << 8 ) & 0xff00ff00);
	n = ((n >> 16 ) & 0x0000ffff) | ((n << 16 ) & 0xffff0000);
	return n;
}


void BitExchange128( uint32_t*bufOut, uint32_t*bufIn )
{
	uint32_t	temp;
	
	temp = revBits( bufIn[0] );
	bufOut[0] = revBits( bufIn[3] );
	bufOut[3] = temp;
	temp = revBits( bufIn[1] );
	bufOut[1] = revBits( bufIn[2] );
	bufOut[2] = temp;
	
}

static FlagStatus AES_Cal_Finished_Flag_Chk( void )
{
	int i;

	for(i = 0; i< 500; i++) {
		if (SET == FL_AES_IsActiveFlag_Complete(AES)) break;
	}
	if(i == 500) return RESET;

	FL_AES_ClearFlag_Complete(AES);
	return SET;
}

int aes_multStart( uint8_t*hParams )
{
	uint32_t	buf[4];
	
	AES_Init(FL_AES_KEY_LENGTH_128B,FL_AES_CIPHER_MULTH,FL_AES_OPERATION_MODE_ENCRYPTION,FL_AES_DATA_TYPE_32B);
	memcpy( buf, hParams, 16 );
	BitExchange128( buf, buf );
	AES_H_WriteEx( ( uint8_t*) buf); //����Multh�����Ĵ���
	memset( buf, 0, 16 );
	AES_IVR_WriteEx( ( uint8_t*) buf );
	FL_AES_Enable( AES ); //����AES
	return 0;
}


int aes_multUpdate(uint8_t*in, uint32_t len)
{
	uint32_t	buf[4];
	int 			i;

	//hash
	if (len == 0) return 0;
	for (i = 0; i<len; i += 16 ) {
		memmove(buf, in, 16);
		BitExchange128(buf, buf);
		if (len - i < 16) 
        {
			memset(buf, 0, 16 -(len - i));
		}
		AES_DIN_GroupWrite_128BIT( ( uint8_t*) buf );
		//�ȴ�CCF��־����,��ɼ����Լ��Ҫ100��ʱ������
		if (RESET == AES_Cal_Finished_Flag_Chk()) return-1;

		in += 16;
	}
	return 0;
}

int aes_multfinish( uint8_t*out, uint32_t len )
{
	uint32_t	outBuf[4];

	AES_IVR_ReadEx( ( uint8_t*) outBuf );
	FL_AES_Disable(AES);//����AESģ��
	BitExchange128( outBuf, outBuf );
	memcpy( out, outBuf, len );
	return len;
}


int aes_CTRInit( CRYPT crypt, uint8_t*key, uint32_t keyLen, uint8_t*iv )
{
	FL_AES_InitTypeDef AES_InitStruct;

	memset( &AES_InitStruct, 0, sizeof( AES_InitStruct ) );
	//���ܲ���
	FL_AES_Disable(AES);//����AESģ��
	AES_InitStruct.cipherMode = FL_AES_CIPHER_CTR; //AES����������ģʽ
	AES_InitStruct.dataType = FL_AES_DATA_TYPE_32B; //AES_DATATYP_8BIT;////32bit����Ĵ������ݽ�������ѡ��
	switch ( keyLen )
	{
		case 16: //128bit
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_128B; //AES������Կ����
			break;

		case 24: //192bit
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_192B; //AES������Կ����
			break;

		case 32: //256bit
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_256B; //AES������Կ����
			break;

		default:
			return-1;
	}

	//AES����ģʽ
	if ( crypt==ENCRYPT ) {
		AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
	}
	else {
		AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
	}

	FL_AES_Init( AES, &AES_InitStruct ); //����AES
	AES_KEY_WriteEx( key, keyLen ); //������Կ

	AES_IVR_WriteEx( iv );			//CTR��CBCģʽ��дAES_IVRx�Ĵ���
	return 0;
}

//ctrMod=0,32λCTR,����128bit
int aes_Crypt( uint8_t*in, uint32_t inLen, uint8_t*out ,int32_t ctrMod)
{
//	uint8_t 	Result = 0;
	uint64_t counter;
	uint8_t 	Buf[16];
	uint8_t 	BufB[16];
	uint16_t	i;
	counter = AES->IVR0;

	FL_AES_Enable(AES);//����AES
	//��������
	for ( i = 0; i<( inLen / 16 ); i++) {
		AES_GroupWriteAndRead_128BIT( in+i*16, out+i*16 );
		if(ctrMod)
		{
			counter++;
			if(counter>0xFFFFFFFF)
			{
				FL_AES_Disable(AES);
				counter = (uint64_t)AES->IVR1+1;
				if(counter>0xFFFFFFFF)
				{
					AES->IVR1=0;
					counter = (uint64_t)AES->IVR2+1;
					if(counter>0xFFFFFFFF)
					{
						AES->IVR2 =0;
						counter = (uint64_t)AES->IVR3+1;
						if(counter>0xFFFFFFFF)
						{
							AES->IVR3 =0;						
						}
					}
				}
				counter=0;
				FL_AES_Enable(AES);
			}
		}
	}
	if ( ( inLen % 16 )!=0 ) {
		memset( Buf, 0, 16 );
		memcpy( Buf, in+i*16, inLen-i*16 );
		AES_GroupWriteAndRead_128BIT( Buf, BufB );
		memcpy( out+i*16, BufB, inLen-i*16 );
	}
	FL_AES_Disable(AES);//����AESģ��
	return inLen;
}


int aes_ECBInit( CRYPT crypt, uint8_t*key, uint32_t keyLen )
{
	FL_AES_InitTypeDef AES_InitStruct;

	memset( &AES_InitStruct, 0, sizeof( AES_InitStruct ) );
	AES_InitStruct.cipherMode = FL_AES_CIPHER_ECB; //AES����������ģʽ
	AES_InitStruct.dataType = FL_AES_DATA_TYPE_32B; //AES_DATATYP_8BIT;////32bit����Ĵ������ݽ�������ѡ��
	switch ( keyLen )
	{
		case 16: //128bit
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_128B; //AES������Կ����
			break;

		case 24: //192bit
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_192B; //AES������Կ����
			break;

		case 32: //256bit
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_256B; //AES������Կ����
			break;

		default:
			return-1;
	}

	//AES����ģʽ
	if ( crypt==ENCRYPT ) {
		AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
	}
	else {
		AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION;
	}

	FL_AES_Init( AES, &AES_InitStruct ); //����AES
	AES_KEY_WriteEx( key, keyLen ); //������Կ
	return 0;
}

int aes_CBCInit(CRYPT crypt,uint8_t*key,uint32_t keyLen,uint8_t* iv)
{
	FL_AES_InitTypeDef AES_InitStruct;
	memset(&AES_InitStruct,0,sizeof(AES_InitStruct));
	switch (keyLen)
	{
		case 16:			
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_128B; //AES������Կ����
			break;
		case 24:			
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_192B; //AES������Կ����
			break;
		case 32:			
			AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_256B; //AES������Կ����
			break;
		default:
			return -1;
	}
	AES_InitStruct.cipherMode = FL_AES_CIPHER_CBC; 				//AES����������ģʽ��AESEN=1ʱ�����޸�
	//AES����ģʽ
	if ( crypt==ENCRYPT ) {
		AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
	}
	else {
		AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION;
	}
	AES_InitStruct.dataType = FL_AES_DATA_TYPE_32B; 	//ѡ���������ͣ�AESEN=1ʱ�����޸ġ����彻������ɲο�AES���������½�

	FL_AES_Init( AES, &AES_InitStruct ); //����AES
	AES_KEY_WriteEx(key,keyLen); //������Կ
	AES_IVR_WriteEx(iv);		//CTR��CBCģʽ��дAES_IVRx�Ĵ���
	return 0;
}



int gcm_hash( uint8_t*hParams, uint8_t*aadBuf, uint32_t aadBufLen, uint8_t*ct, uint32_t ctLen,
	 uint8_t*tag, uint32_t tagLen )
{
	uint32_t	buff[4];

	aes_multStart( hParams );
	aes_multUpdate( aadBuf, aadBufLen );
	aes_multUpdate( ct, ctLen );
	memset( buff, 0, 16 );
	int2Byte_MSB( ( aadBufLen << 3 ), ( uint8_t*) ( buff+1 ) );
	int2Byte_MSB( ( ctLen << 3 ), ( uint8_t*) ( buff+3 ) );
	aes_multUpdate( ( uint8_t*) buff, 16 );
	aes_multfinish( ( uint8_t*) buff, 16 );
	memcpy( tag, buff, tagLen );
	return 0;
}


int gcm_AEk( uint8_t*key, uint32_t keyLen, uint8_t*ivrBuf, uint32_t ivLen, uint8_t*aadBuf,
	 uint32_t aadBufLen, uint8_t*pt, uint32_t ptLen, uint8_t*ct, uint32_t ctLen, uint8_t*tag,
	 uint32_t tagLen )
{
	uint32_t	subKey[4];
	uint32_t	J0[4];
	uint32_t	hash[4];

	//��һ����ʹ��key��128bit�������ECB���ܣ��õ�subKey H
	memset( subKey, 0, sizeof( subKey ) );
	aes_ECBInit(ENCRYPT,key,keyLen);
	aes_Crypt( ( uint8_t*) subKey, sizeof( subKey ), ( uint8_t*) subKey ,0);
	//�ڶ��������ǰ������ Y0��J0
	if ( ivLen==( 96 / 8 ) ) {
		//		1�����IV=96,��IV||COUNTER,COUNTER=1
		memcpy( J0, ivrBuf, 12 );
		J0[3] 		= 0x01000000; 	//��һ��ʹ��ʱ��Ҫcounter+1
	}
	else {
		//		2������GHASH(subkey,null,IV)
		gcm_hash( ( uint8_t*) subKey, NULL, 0, ivrBuf, ivLen, ( uint8_t*) J0, 16 );
	}
	J0[3] 		= __REV( __REV( J0[3] )+1 );
	//�������������� P ��� CTR���ܵ�Yi���õ����� C
	if ( ptLen ) {
		aes_CTRInit( ENCRYPT, key, keyLen, ( uint8_t*) J0 );
		aes_Crypt( pt, ptLen, ct ,0);
	}
	//���Ĳ������ζ� a����ĸ�����Ϣ��A������C��len(A)||len(C)ģ�˵�һ����subkey H
	gcm_hash( ( uint8_t*) subKey, aadBuf, aadBufLen, ct, ctLen, ( uint8_t*) hash, sizeof( hash ) );
	//���岽����keyΪ����,Y0/J0ΪIV���Ե��岽��GHASHֵ����CTR���ܣ�Ȼ��bit����Ϊ��ˣ����ɵõ����ݱ�ǩ tag
	J0[3] 		= __REV( __REV( J0[3] )-1 );
	aes_CTRInit( ENCRYPT, key, keyLen, ( uint8_t*) J0 );
	aes_Crypt( ( uint8_t*) hash, sizeof( hash ), ( uint8_t*) hash ,0);
	memcpy( tag, hash, tagLen );

	return 0;
}


int gcm_ADk( uint8_t*key, uint32_t keyLen, uint8_t*ivrBuf, uint32_t ivLen, uint8_t*aadBuf,
	 uint32_t aadBufLen, uint8_t*ct, uint32_t ctLen, uint8_t*pt, uint32_t ptLen, uint8_t*tag,
	 uint32_t tagLen )
{
	uint32_t	tagTemp[4];
	uint32_t	subKey[4];
	uint32_t	J0[4];

	//��һ����ʹ��key��128bit�������ECB���ܣ��õ�subKey H
	memset( subKey, 0, sizeof( subKey ) );
	aes_ECBInit( ENCRYPT, key, keyLen );
	aes_Crypt( ( uint8_t*) subKey, sizeof( subKey ), ( uint8_t*) subKey ,0);
	//�ڶ��������ǰ������ Y0��J0
	if ( ivLen==( 96 / 8 ) ) {
		//		1�����IV=96,��IV||COUNTER,COUNTER=1
		memcpy( J0, ivrBuf, 12 );
		J0[3] 		= 0x01000000; 	//��һ��ʹ��ʱ��Ҫcounter+1
	}
	else {
		//		2������GHASH(subkey,null,IV)
		gcm_hash( ( uint8_t*) subKey, NULL, 0, ivrBuf, ivLen, ( uint8_t*) J0, 16 );
	}
	//���Ĳ������ζ� a����ĸ�����Ϣ��A������C��len(A)||len(C)ģ�˵�һ����subkey H
	gcm_hash( ( uint8_t*) subKey, aadBuf, aadBufLen, ct, ctLen, ( uint8_t*) tagTemp, 16 );

	//���岽����keyΪ����,Y0/J0ΪIV���Ե��岽��GHASHֵ����CTR���ܣ�Ȼ��bit����Ϊ��ˣ����ɵõ����ݱ�ǩ tag
	aes_CTRInit( ENCRYPT, key, keyLen, ( uint8_t*) J0 );
	aes_Crypt( ( uint8_t*)tagTemp, 16, ( uint8_t*)tagTemp ,0);
	if ( memcmp( tagTemp, tag, tagLen )!=0 ) {
		return-1;
	}
	//�������������� P ��� CTR���ܵ�Yi���õ����� C
	J0[3] 		= __REV( __REV( J0[3] )+1 );
	aes_CTRInit( ENCRYPT, key, keyLen, ( uint8_t*) J0 );
	aes_Crypt( ct, ctLen, pt ,0);
	return 0;
}

ErrorStatus Test_AES_IV_96Bit_GCM128Bit(void)
{
	int result = -1;
	uint8_t encryptInBuf[13] = {0xC0, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x02, 0x00};
	uint8_t aadBuf[17] = {0x30, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF};
	uint8_t keyBuf[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
	uint8_t ivrBuf[12] = {0x4D, 0x4D, 0x4D, 0x00, 0x00, 0xBC, 0x61, 0x4E, 0x01, 0x23, 0x45, 0x67};
	/* const uint8_t scrTag[12] = {0x7d, 0x82, 0x5c, 0x3b, 0xe4, 0xa7, 0x7c, 0x3f, 0xcc, 0x05, 0x6b, 0x6b}; */

	uint8_t EncryptBuf[16];
	uint8_t Tag[16];
	uint8_t DecryptBuf[16];	
	
	result = gcm_AEk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	 
	result = gcm_ADk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	if(result != 0) return FAIL;
	return PASS;
}

ErrorStatus Test_AES_IV_Not96Bit_GCM128Bit(void)
{
	int result = -1;
	uint8_t encryptInBuf[16] = {0x2D, 0x4D, 0x25, 0x20, 0x77, 0x62, 0x6C, 0xDE, 0x15, 0x1D, 0xBE, 0x3F, 0x4B, 0x7E, 0xA2, 0xE4};
	uint8_t aadBuf[16] = {0xCC, 0x9F, 0xB0, 0x86, 0x87, 0x42, 0x7C, 0x57, 0x04, 0x2E, 0x36, 0x9B, 0x28, 0x6E, 0x4D, 0x5A};
	uint8_t keyBuf[16] = {0x59, 0x50, 0x45, 0x55, 0xAD, 0x1F, 0x96, 0xDF, 0x17, 0x1E, 0xDF, 0xC3, 0x06, 0x5B, 0xD3, 0x6D};
	uint8_t ivrBuf[1] = {0xCA};
	/* const uint8_t scrTag[4] = {0x1F, 0x52, 0x05, 0x82}; */

	uint8_t EncryptBuf[16];
	uint8_t Tag[16];
	uint8_t DecryptBuf[16];	
	
	result = gcm_AEk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	 
	result = gcm_ADk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	if(result != 0) return FAIL;
	return PASS;
}

/*AES GCM256Bit ������ֻҪ��keyBuf������ĳ�32�ֽ����飬��Կ������������Ϊ256Bit*/

ErrorStatus Test_AES_IV_96Bit_GCM256Bit(void)
{
	int result = -1;
	uint8_t encryptInBuf[13] = {0xC0, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x02, 0x00};
	uint8_t aadBuf[17] = {0x30, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF};
	uint8_t keyBuf[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
	uint8_t ivrBuf[12] = {0x4D, 0x4D, 0x4D, 0x00, 0x00, 0xBC, 0x61, 0x4E, 0x01, 0x23, 0x45, 0x67};
	/* const uint8_t scrTag[12] = {0xD5, 0xB6, 0xD5, 0x12, 0xEE, 0x23, 0xBB, 0x5D, 0xE3, 0x40, 0x65, 0x23}; */

	uint8_t EncryptBuf[16];
	uint8_t Tag[16];
	uint8_t DecryptBuf[16];	
	
	result = gcm_AEk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	 
	result = gcm_ADk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	if(result != 0) return FAIL;
	return PASS;
}

/*AES GCM192Bit ������ֻҪ��keyBuf������ĳ�324�ֽ����飬��Կ������������Ϊ192Bit*/

ErrorStatus Test_AES_IV_96Bit_GCM192Bit(void)
{
	int result = -1;
	uint8_t encryptInBuf[13] = {0xC0, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x02, 0x00};
	uint8_t aadBuf[17] = {0x30, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF};
	uint8_t keyBuf[24] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
	uint8_t ivrBuf[12] = {0x4D, 0x4D, 0x4D, 0x00, 0x00, 0xBC, 0x61, 0x4E, 0x01, 0x23, 0x45, 0x67};
	/* const uint8_t scrTag[12] = {0x76, 0xF2, 0x3D, 0xE8, 0x5A, 0x54, 0x24, 0x04, 0x05, 0xB7, 0x14, 0x5D}; */

	uint8_t EncryptBuf[16];
	uint8_t Tag[16];
	uint8_t DecryptBuf[16];	
	
	result = gcm_AEk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	 
	result = gcm_ADk( keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag) );
	if(result != 0) return FAIL;
	return PASS;
}
