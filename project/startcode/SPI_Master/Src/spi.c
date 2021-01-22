#include "spi.h"

void SpiInit(void)
{
	FL_GPIO_InitTypeDef gpioInitStruct = {0};
    FL_SPI_InitTypeDef spiInitStruct = {0};
    
    spiInitStruct.baudRate = FL_SPI_BAUDRATE_DIV2;
    spiInitStruct.bitOrder = FL_SPI_BIT_ORDER_MSB_FIRST;
    spiInitStruct.clockPhase = FL_SPI_PHASE_EDGE1;
    spiInitStruct.clockPolarity = FL_SPI_POLARITY_NORMAL;
    spiInitStruct.dataWidth = FL_SPI_DATA_WIDTH_8B;
    spiInitStruct.mode = FL_SPI_WORK_MODE_MASTER;
    spiInitStruct.softControl = ENABLE;
    spiInitStruct.transferMode = FL_SPI_TRANSFER_MODE_FULL_DUPLEX;
    FL_SPI_Init(SPI1, &spiInitStruct);
    
    FL_SPI_ClearTXBuff(SPI1);
    FL_SPI_ClearRXBuff(SPI1);
    
    gpioInitStruct.pin = FL_GPIO_PIN_2 | FL_GPIO_PIN_3 | FL_GPIO_PIN_4 |
        FL_GPIO_PIN_5;
    gpioInitStruct.mode = FL_GPIO_MODE_DIGITAL;
    gpioInitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    gpioInitStruct.pull = DISABLE;
    gpioInitStruct.remapPin = DISABLE;
    
    FL_GPIO_Init(GPIOD, &gpioInitStruct);
}

uint32_t SpiWriteAndRead(uint32_t data)
{
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);
    
    FL_SPI_WriteTXBuff(SPI1, data);
    while (!(FL_SPI_IsActiveFlag_TXBuffEmpty(SPI1)));
    while (!(FL_SPI_IsActiveFlag_RXBuffFull(SPI1)));
    data = FL_SPI_ReadRXBuff(SPI1);
    
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);
    return data;
}

void SpiWriteData(uint8_t *data, uint16_t length)
{
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);
    while (length--)
    {
        FL_SPI_WriteTXBuff(SPI1, *data); data++;
        while (!(FL_SPI_IsActiveFlag_TXBuffEmpty(SPI1)));
    }
    while (!(FL_SPI_IsActiveFlag_RXBuffFull(SPI1)));
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);
}

void SpiReadData(uint8_t *data, uint16_t length)
{
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);
    while (length--)
    {
        FL_SPI_WriteTXBuff(SPI1, 0x55);
        while (!(FL_SPI_IsActiveFlag_RXBuffFull(SPI1)));
        *data = FL_SPI_ReadRXBuff(SPI1); data++;
    }
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);
}
