#include "main.h"
#include "rng.h"

///* crc32ʵ�ֺ��� = CRC-32/MPEG-2       x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1 */
//static uint32_t Calc_Crc32_MPEG2(const uint8_t *data, uint32_t len)
//{
//    uint32_t crc = 0XFFFFFFFF;
//    uint32_t i = 0, j = 0;
//    while((len--)!=0)
//    {
//        crc ^= (uint32_t)*(data + j) <<24;
//		j++;
//		for (i = 0; i < 8; i++)
//		{
//			if((crc&0x80000000) !=0)	
//			{
//				crc = (crc<<1)^0x4C11DB7;
//			}
//			else
//			{
//				crc<<=1;
//			}
//		}
//    }
//    return crc;
//}

/* RNG��ʼ�� */
ErrorStatus RNG_Init(void)
{
	FL_RNG_InitTypeDef initStruct;
    /* RNG Clock ��Ƶϵ��*/
	initStruct.prescaler = FL_RCC_RNG_PSC_DIV2;
	return FL_RNG_Init(RNG,&initStruct);
}

ErrorStatus Test_RNG(void)
{
	uint32_t rn32,crc32;
    rn32 =  GetRandomNumber();
	if(rn32 == 0xFFFFFFFF)
	{
		return FAIL;
	}
	crc32 = GetCrc32(rn32);
	if(crc32 == 0xFFFFFFFF)
	{
		return FAIL;
	}
//	/* �Ƚ�����㷨��ģ�����Ľ��������鿴�����ȷ�ԣ�����������ģ������Ӳ�㷨����Ĵ����ע�ͣ� */
//	{
//		uint8_t buffer[4];
//		uint32_t crc32_MPEG2;
//		buffer[0] = rn32 >> 24;
//		buffer[1] = rn32 >> 16;
//		buffer[2] = rn32 >> 8;
//		buffer[3] = rn32;
//		crc32_MPEG2 = Calc_Crc32_MPEG2(buffer,sizeof(buffer));
//		if(crc32_MPEG2 != crc32)
//		{
//			return FAIL;
//		}
//	}
	return PASS;
}
