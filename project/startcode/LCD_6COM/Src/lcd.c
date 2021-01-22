#include "lcd.h"

void LcdInit(void)
{
    FL_GPIO_InitTypeDef gpioInitStruction;
    FL_LCD_InitTypeDef lcdInitStruction;
    
    // GPIO Init
    gpioInitStruction.mode = FL_GPIO_MODE_ANALOG;
    gpioInitStruction.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    gpioInitStruction.pull = DISABLE;
    
    gpioInitStruction.pin = FL_GPIO_PIN_0 | FL_GPIO_PIN_1 | FL_GPIO_PIN_2 | 
        FL_GPIO_PIN_3 | FL_GPIO_PIN_4 | FL_GPIO_PIN_5 | FL_GPIO_PIN_8 | 
        FL_GPIO_PIN_9 | FL_GPIO_PIN_10;
    FL_GPIO_Init(GPIOA, &gpioInitStruction);
    
    gpioInitStruction.pin = FL_GPIO_PIN_4 | FL_GPIO_PIN_5 | FL_GPIO_PIN_6 |
        FL_GPIO_PIN_7 | FL_GPIO_PIN_8 | FL_GPIO_PIN_9 | FL_GPIO_PIN_10 |
        FL_GPIO_PIN_11 | FL_GPIO_PIN_13 | FL_GPIO_PIN_14;
    FL_GPIO_Init(GPIOB, &gpioInitStruction);
    
    gpioInitStruction.pin = FL_GPIO_PIN_4 | FL_GPIO_PIN_5 | FL_GPIO_PIN_6 |
        FL_GPIO_PIN_7 | FL_GPIO_PIN_8 | FL_GPIO_PIN_9 | FL_GPIO_PIN_10 |
        FL_GPIO_PIN_11 | FL_GPIO_PIN_12;
    FL_GPIO_Init(GPIOC, &gpioInitStruction);
    
    gpioInitStruction.pin = FL_GPIO_PIN_0;
    FL_GPIO_Init(GPIOD, &gpioInitStruction);
    
    // LCD Init
    lcdInitStruction.biasCurrent = FL_LCD_BIAS_CURRENT_HIGH;
    lcdInitStruction.biasMode = FL_LCD_BIAS_MODE_3BIAS;
    lcdInitStruction.biasVoltage = FL_LCD_BIAS_VOLTAGE_LEVEL10;
    lcdInitStruction.COMxNum = FL_LCD_COM_NUM_6COM;
    lcdInitStruction.waveform = FL_LCD_WAVEFORM_TYPEA;
    lcdInitStruction.displayFreq = 64;
    lcdInitStruction.mode = FL_LCD_DRIVER_MODE_INNER_RESISTER;
    FL_LCD_Init(LCD, &lcdInitStruction);
    
    // COM and SEG Init
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM0);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM1);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM2);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM3);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM4);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM5);

    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG0);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG1);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG2);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG3);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG4);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG5);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG6);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG7);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG8);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG9);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG10);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG11);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG12);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG13);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG14);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG15);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG16);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG17);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG18);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG19);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG20);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG21);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG22);
    
    FL_LCD_Enable(LCD);
}

void LcdDisplayAll(bool state)
{
    if (state == true)
    {
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG0, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG1, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG2, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG3, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG4, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG5, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG6, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG7, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG8, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG9, 0xffffffff);
    }
    else
    {
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG0, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG1, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG2, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG3, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG4, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG5, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG6, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG7, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG8, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG9, 0x00000000);
    }
}

//0~9, A,B, C, D, E, F, 空
const uint8_t FONT_CODE_TABLE[] = { 
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
    0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00}; 

uint32_t dispBuf[10] = {0};

void LcdDisplayRefresh(void)
{
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG0, dispBuf[0]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG1, dispBuf[1]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG2, dispBuf[2]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG3, dispBuf[3]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG4, dispBuf[4]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG5, dispBuf[5]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG6, dispBuf[6]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG7, dispBuf[7]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG8, dispBuf[8]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG9, dispBuf[9]);
}

// true: 点亮; false: 熄灭
void LcdDisplayBIT(uint32_t x, uint32_t y, bool value)
{    
    FL_LCD_6COMDisplay(dispBuf, x - 1, y - 1, value);
    LcdDisplayRefresh();
}

void LcdDisplayNumber(uint32_t number)
{      
    uint8_t digit = 8;
    uint8_t font; 
    
    while (digit)
    {
        font = FONT_CODE_TABLE[number % 10];
        number /= 10;
        
        switch (digit--)
        {
        case 0x08:
            //------------ 第8个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 10, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 10, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 10, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 9, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 9, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 9, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 9, (font & 0x40) >> 6);
            break;

        case 0x07:
            //------------ 第7个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 8, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 8, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 8, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 7, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 7, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 7, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 7, (font & 0x40) >> 6);
            break;
    
        case 0x06:
            //------------ 第6个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 6, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 6, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 6, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 5, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 5, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 5, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 5, (font & 0x40) >> 6);
            break;	
        
        case 0x05:
            //------------ 第5个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 13, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 13, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 13, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 14, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 14, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 14, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 14, (font & 0x40) >> 6);
            break;	

        case 0x04:
            //------------ 第4个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 15, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 15, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 15, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 16, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 16, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 16, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 16, (font & 0x40) >> 6);
            break;	
    
        case 0x03:
            //------------ 第3个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 17, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 17, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 17, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 18, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 18, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 18, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 18, (font & 0x40) >> 6);
            break;	
        
        case 0x02:
            //------------ 第2个"8"字符 ----------	
            FL_LCD_6COMDisplay(dispBuf, 1, 19, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 19, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 19, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 20, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 20, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 20, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 20, (font & 0x40) >> 6);
            break;	
    
        case 0x01:
            //------------ 第1个"8"字符 ----------
            FL_LCD_6COMDisplay(dispBuf, 1, 21, (font & 0x01) >> 0);
            FL_LCD_6COMDisplay(dispBuf, 2, 21, (font & 0x02) >> 1);
            FL_LCD_6COMDisplay(dispBuf, 3, 21, (font & 0x04) >> 2);
            FL_LCD_6COMDisplay(dispBuf, 4, 22, (font & 0x08) >> 3);
            FL_LCD_6COMDisplay(dispBuf, 3, 22, (font & 0x10) >> 4);
            FL_LCD_6COMDisplay(dispBuf, 1, 22, (font & 0x20) >> 5);
            FL_LCD_6COMDisplay(dispBuf, 2, 22, (font & 0x40) >> 6);
            break;
        }
    }
    
    LcdDisplayRefresh();
}
