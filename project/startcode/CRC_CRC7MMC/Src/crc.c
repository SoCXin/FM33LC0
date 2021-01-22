#include "crc.h"

__STATIC_INLINE uint8_t CRC7_MMC(uint8_t *data, uint32_t length)
{
    while (length--)
    {
        FL_CRC_WriteData(CRC, *data++);
        while (FL_CRC_IsActiveFlag_Busy(CRC));
    }
    
    return FL_CRC_ReadData(CRC) & 0x7f;
}

__STATIC_INLINE uint8_t CRC8(uint8_t *data, uint32_t length)
{
    while (length--)
    {
        FL_CRC_WriteData(CRC, *data++);
        while (FL_CRC_IsActiveFlag_Busy(CRC));
    }
    
    return FL_CRC_ReadData(CRC) & 0xff;
}

__STATIC_INLINE uint16_t CRC16_CCITT(uint8_t *data, uint32_t length)
{
    while (length--)
    {
        FL_CRC_WriteData(CRC, *data++);
        while (FL_CRC_IsActiveFlag_Busy(CRC));
    }
    
    return FL_CRC_ReadData(CRC) & 0xffff;
}

__STATIC_INLINE uint32_t CRC32(uint8_t *data, uint32_t length)
{
    while (length--)
    {
        FL_CRC_WriteData(CRC, *data++);
        while (FL_CRC_IsActiveFlag_Busy(CRC));
    }
    
    return FL_CRC_ReadData(CRC);
}

__STATIC_INLINE uint16_t CRC16_CCITT_WORD(uint32_t *data, uint32_t length)
{
    while (length--)
    {
        FL_CRC_WriteData(CRC, *data++);
        while (FL_CRC_IsActiveFlag_Busy(CRC));
    }
    
    return FL_CRC_ReadData(CRC) & 0xffff;
}


//__STATIC_INLINE uint16_t CRC16_CCITT_DMA(uint8_t *data, uint32_t length)
//{
//    FL_CRC_InitTypeDef CRC_InitStruct;
//    FL_DMA_InitTypeDef DMA_InitStruct;

//    DMA_InitStruct.circMode = DISABLE;
//    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
//    DMA_InitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;
//    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
//    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;
//    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION5;
//    DMA_InitStruct.memoryAddress = (uint32_t)data;
//    DMA_InitStruct.nbData = length - 1;
//    FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_0);
//    
//    FL_DMA_Enable(DMA);
//    

//    CRC_InitStruct.calculatMode = FL_CRC_CALCULATE_SERIAL;
//    CRC_InitStruct.dataWidth = FL_CRC_DATA_WIDTH_8B;
//    CRC_InitStruct.initVal = 0x0000;
//    CRC_InitStruct.polynomial = 0x1021;
//    CRC_InitStruct.polynomialWidth = FL_CRC_POLYNOMIAL_16B;
//    CRC_InitStruct.reflectIn = FL_CRC_INPUT_INVERT_BYTE;
//    CRC_InitStruct.reflectOut = FL_CRC_OUPUT_INVERT_BYTE;
//    CRC_InitStruct.xorReg = 0x0000;
//    CRC_InitStruct.xorRegState = DISABLE;
//    FL_CRC_Init(CRC, &CRC_InitStruct);


//    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);
//    FL_DMA_EnableChannel(DMA, FL_DMA_CHANNEL_0);
//    while (!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0));
//    FL_DMA_Disable(DMA);
//    
//    return FL_CRC_ReadData(CRC) & 0xffff;
//}

//__STATIC_INLINE uint16_t CRC16_CCITT_WORD_DMA(uint32_t *data, uint32_t length)
//{
//    FL_CRC_InitTypeDef CRC_InitStruct;
//    FL_DMA_InitTypeDef DMA_InitStruct;
//    
//    DMA_InitStruct.circMode = DISABLE;
//    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_32B;
//    DMA_InitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;
//    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
//    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;
//    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION5;
//    DMA_InitStruct.memoryAddress = (uint32_t)data;
//    DMA_InitStruct.nbData = length - 1;
//    FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_0);
//    
//    FL_DMA_Enable(DMA);
//    
//    CRC_InitStruct.calculatMode = FL_CRC_CALCULATE_SERIAL;
//    CRC_InitStruct.dataWidth = FL_CRC_DATA_WIDTH_32B;
//    CRC_InitStruct.initVal = 0x0000;
//    CRC_InitStruct.polynomial = 0x1021;
//    CRC_InitStruct.polynomialWidth = FL_CRC_POLYNOMIAL_16B;
//    CRC_InitStruct.reflectIn = FL_CRC_INPUT_INVERT_WORD;
//    CRC_InitStruct.reflectOut = FL_CRC_OUPUT_INVERT_BYTE;
//    CRC_InitStruct.xorReg = 0x0000;
//    CRC_InitStruct.xorRegState = DISABLE;
//    FL_CRC_Init(CRC, &CRC_InitStruct);

//    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);
//    FL_DMA_EnableChannel(DMA, FL_DMA_CHANNEL_0);
//    while (!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0));
//    FL_DMA_Disable(DMA);
//    
//    return FL_CRC_ReadData(CRC) & 0xffff;
//}



#define DATA_LENGTH     8
static uint8_t DATA[DATA_LENGTH] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

#define DATA1_LENGTH    2
static uint32_t DATA1[DATA1_LENGTH] = {0x01020304, 0x05060708};

ErrorStatus Test_CRC7_MMC(void)
{
    uint32_t result = 0;  
    result = CRC7_MMC(DATA, DATA_LENGTH);
    if (result != 0x57) return FAIL;
    return PASS;    
}

ErrorStatus Test_CRC8(void)
{
    uint32_t result = 0;  
    result = CRC8(DATA, DATA_LENGTH);
    if (result != 0x3E) return FAIL;
    return PASS; 
}

ErrorStatus Test_CRC16_CCITT(void)
{
    uint32_t result = 0;  
    result = CRC16_CCITT(DATA, DATA_LENGTH);
    if (result != 0xEEA7) return FAIL;
    return PASS; 
}

ErrorStatus Test_CRC32(void)
{
    uint32_t result = 0;  
    result = CRC32(DATA, DATA_LENGTH);
    if (result != 0x3FCA88C5) return FAIL;
    return PASS;
}

ErrorStatus Test_CRC16_CCITT_WORD(void)
{
    uint32_t result = 0;  
    result = CRC16_CCITT_WORD(DATA1, DATA1_LENGTH);
    if (result != 0xEEA7) return FAIL;
    return PASS;
}

//ErrorStatus Test_CRC16_CCITT_DMA(void)
//{
//    uint32_t result = 0;  
//    result = CRC16_CCITT_DMA(DATA, DATA_LENGTH);
//    if (result != 0xEEA7) return FAIL;
//    return PASS;
//}

//ErrorStatus Test_CRC16_CCITT_WORD_DMA(void)
//{
//    uint32_t result = 0;  
//    result = CRC16_CCITT_WORD_DMA(DATA1, DATA1_LENGTH);
//    if (result != 0xEEA7) return FAIL;
//    return PASS;
//}
