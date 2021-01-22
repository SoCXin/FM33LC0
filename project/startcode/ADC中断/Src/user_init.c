#include "user_init.h"

void ClockInit(uint32_t clock)
{
    switch (clock)
    {
        case FL_RCC_RCHF_FREQUENCY_8MHZ:
            FL_RCC_RCHF_WriteTrimValue(RCHF8M_TRIM);
            break;
        
        case FL_RCC_RCHF_FREQUENCY_16MHZ:
            FL_RCC_RCHF_WriteTrimValue(RCHF16M_TRIM);
            break;
        
        case FL_RCC_RCHF_FREQUENCY_24MHZ:
            FL_RCC_RCHF_WriteTrimValue(RCHF24M_TRIM);
            break;
        
        default:
            FL_RCC_RCHF_WriteTrimValue(RCHF8M_TRIM);
            break;
    }
    
    FL_RCC_RCHF_SetFrequency(clock);
    FL_RCC_SetSystemClockSource(FL_RCC_SYSTEM_CLK_SOURCE_RCHF);
}

static void SystickInit(void)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void FoutInit(void)
{
    FL_GPIO_InitTypeDef init = {0};
    
    init.pin = FL_GPIO_PIN_11;
    init.mode = FL_GPIO_MODE_DIGITAL;
    init.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    init.pull = DISABLE;
    FL_GPIO_Init(GPIOD, &init);
    
    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_AHBCLK_DIV64);
}

#ifndef MFANG
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
    int handle; 
}; 
FILE __stdout;    

//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
    x = x; 
} 

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
    FL_UART_WriteTXBuff(UART0, (uint8_t)ch);
    while(FL_UART_IsActiveFlag_TXBuffEmpty(UART0) != SET);
    return ch;
}

void DebugUartInit(void)
{
     FL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    FL_UART_InitTypeDef UART_InitStruct = {0};   

    //PA13:UART0-RX   PA14:UART0-TX
    GPIO_InitStruct.pin        = FL_GPIO_PIN_13|FL_GPIO_PIN_14;
    GPIO_InitStruct.mode       = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;   
    GPIO_InitStruct.pull       = ENABLE;
    GPIO_InitStruct.remapPin = DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    UART_InitStruct.clockSrc = FL_RCC_UART0_CLK_SOURCE_APB1CLK;
	
	UART_InitStruct.baudRate            = 115200;							        //波特率
	UART_InitStruct.dataWidth           = FL_UART_DATA_WIDTH_8B;			      	//数据位数
	UART_InitStruct.stopBits            = FL_UART_STOP_BIT_WIDTH_1B;				//停止位
	UART_InitStruct.parity              = FL_UART_PARITY_EVEN;				        //奇偶校验
	UART_InitStruct.transferDirection   = FL_UART_DIRECTION_TX_RX;	                //接收-发送使能
	FL_UART_Init(UART0, &UART_InitStruct);	
}

void LedInit(void)
{
    uint8_t count = 5;
    
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};
   
    FL_GPIO_ResetOutputPin(LED0_GPIO, LED0_PIN);
    
    GPIO_InitStruct.pin = LED0_PIN;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    FL_GPIO_Init(LED0_GPIO, &GPIO_InitStruct);
    
    while (count--)
    {
        LED0_ON();
        DelayMs(100);
		LED0_OFF();
		DelayMs(100);
    }
}

#endif 

void UserInit(void)
{
    SystickInit();
    
#ifndef MFANG
    LedInit();
    DebugUartInit();
#endif
}

void DelayUs(uint32_t count)
{
    count = (uint64_t)FL_RCC_GetSystemClockFreq() * count / 1000000;
    count = count > 16777216 ? 16777216 : count;
    
    SysTick->LOAD = count - 1;
    SysTick->VAL = 0;
    while (!((SysTick->CTRL >> 16) & 0x1));
}

void DelayMs(uint32_t count)
{
    while (count--)
    {
        DelayUs(1000);
    }
}
