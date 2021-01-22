#include "lcd.h"
#include "user_init.h"

// Device IC: ST7789VW
// Interface: 4 Line SPI
// Resolution: 240(H)RGB x 320(V)
// Pin Assignment
// 1: GND
// 2: LEDK
// 3: LEDA  (IO)
// 4: VDD
// 5: GND
// 6: GND
// 7: D/C   (SPI)
// 8: CS    (SPI)
// 9: SCL   (SPI)
// 10: SDA  (SPI)
// 11: RESET(IO)
// 12: GND

#define LCD_RESET_SET() LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_9)
#define LCD_RESET_RST() LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_9)

#define LCD_BACKLIGHT_SET() LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10)
#define LCD_BACKLIGHT_RST() LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10)

void LcdInit(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    SpiInit();
    
    LCD_RESET_SET();
    LCD_BACKLIGHT_SET();
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = DISABLE;
    
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    // Reset
    LCD_RESET_SET();
    DelayMs(1);
    LCD_RESET_RST();
    DelayMs(2);
    LCD_RESET_SET();
    DelayMs(3);
    
    // Exit power sleep mode
    DelayMs(5);
    SpiWriteCmd(0x11);
    DelayMs(120);
    
    // Config
    SpiWriteCmd(0xb2);
    SpiWriteData(0x0c);
    SpiWriteData(0x0c);
    SpiWriteData(0x00);
    SpiWriteData(0x33);
    SpiWriteData(0x33);
    
    SpiWriteCmd(0xb7);
    SpiWriteData(0x35);
    
    SpiWriteCmd(0xbb);
    SpiWriteData(0x19);
    
    SpiWriteCmd(0xc0);
    SpiWriteData(0x2c);
    
    SpiWriteCmd(0xc2);
    SpiWriteData(0x01);
    
    SpiWriteCmd(0xc3);
    SpiWriteData(0x12);
    
    SpiWriteCmd(0xc4);
    SpiWriteData(0x20);
    
    SpiWriteCmd(0xc6);
    SpiWriteData(0x0f);
    
    SpiWriteCmd(0xd0);
    SpiWriteData(0xa4);
    SpiWriteData(0xa1);
    
    SpiWriteCmd(0x36);
    // C0-����ģʽ��RGBģʽ
    // C8-����ģʽ��BGRģʽ
    // A0-����ģʽ��RGBģʽ
    // A8-����ģʽ��BGRģʽ
    SpiWriteData(0xa0);
    
    SpiWriteCmd(0xe0);
    SpiWriteData(0xd0);
    SpiWriteData(0x04);
    SpiWriteData(0x0d);
    SpiWriteData(0x11);
    SpiWriteData(0x13);
    SpiWriteData(0x2b);
    SpiWriteData(0x3f);
    SpiWriteData(0x54);
    SpiWriteData(0x4c);
    SpiWriteData(0x18);
    SpiWriteData(0x0d);
    SpiWriteData(0x0b);
    SpiWriteData(0x1f);
    SpiWriteData(0x23);
    
    SpiWriteCmd(0xe1);
    SpiWriteData(0xd0);
    SpiWriteData(0x04);
    SpiWriteData(0x0c);
    SpiWriteData(0x11);
    SpiWriteData(0x13);
    SpiWriteData(0x2c);
    SpiWriteData(0x3f);
    SpiWriteData(0x44);
    SpiWriteData(0x51);
    SpiWriteData(0x2f);
    SpiWriteData(0x1f);
    SpiWriteData(0x1f);
    SpiWriteData(0x20);
    SpiWriteData(0x23);
    
    SpiWriteCmd(0x21);
    
    SpiWriteCmd(0x3a);
    SpiWriteData(0x05);
    
    SpiWriteCmd(0x29);
    
    LcdClear(WHITE);
}

/**
 * @brief   ������ʾ����
 * @param   x1: x����ʾ��ʼλ�á�
 * @param   x2: x����ʾ����λ��
 * @param   y1: y����ʾ��ʼλ�á�
 * @param   y2: y����ʾ����λ�á�
 * @return  �ޡ�
 */
void LcdSetPosition(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{
    SpiWriteCmd(0x2a);
    SpiData16Bit();
    SpiWriteData(x1);
    SpiWriteData(x2);
    SpiData8Bit();
    
    SpiWriteCmd(0x2b);
    SpiData16Bit();
    SpiWriteData(y1);
    SpiWriteData(y2);
    SpiData8Bit();
}

/**
 * @brief   ��ָ���������ָ������ɫ��
 * @param   x: ��������x����ʼλ�á�
 * @param   y: ��������y����ʼλ�á�
 * @param   length: �������ĳ��ȡ�
 * @param   height: �������ĸ߶ȡ�
 * @param   color: �����ɫ��
 * @return  �ޡ�
 */
void LcdFill(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color)
{
    int i = 0, j = 0;
    
    LcdSetPosition(x, x + length, y, y + height);
    
    SpiWriteCmd(0x2c);   
    SpiData16Bit();
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < height; j++)
        {
            SpiWriteData(color);
        }
    }
    SpiData8Bit();
    SpiWriteCmd(0x29);
}

/**
 * @brief   ʹ��ָ����ɫ����
 * @param   color: ����������ɫ��
 * @return  �ޡ�
 */
void LcdClear(uint16_t color)
{
    LcdFill(0, 0, 320, 240, color);
}

/**
 * @brief   ��ȡ������ϢID��Ϣ
 * @param   *id, LCD������ID��Ϣ��  
 * @return  �ޡ�
 */
void LcdReadID(uint8_t *id)
{
    SpiReadData(0x04, id, 4);
}


