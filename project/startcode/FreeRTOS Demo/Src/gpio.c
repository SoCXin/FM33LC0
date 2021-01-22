#include "gpio.h"
#include "fm33lc0xx_fl_gpio.h"

void GPIO_Init(void)
{
    FL_GPIO_InitTypeDef         GPIO_InitStruct;
  
    GPIO_InitStruct.pin        = FL_GPIO_PIN_4|FL_GPIO_PIN_5|FL_GPIO_PIN_6|FL_GPIO_PIN_7;
	GPIO_InitStruct.mode       = FL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.pull       = DISABLE;
	GPIO_InitStruct.remapPin   = DISABLE;	
	FL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
    GPIO_InitStruct.pin        = FL_GPIO_PIN_0|FL_GPIO_PIN_1|FL_GPIO_PIN_2|FL_GPIO_PIN_3;
	GPIO_InitStruct.mode       = FL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.pull       = DISABLE;
	GPIO_InitStruct.remapPin   = DISABLE;	
	FL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
    GPIO_InitStruct.pin        = FL_GPIO_PIN_0|FL_GPIO_PIN_1;
	GPIO_InitStruct.mode       = FL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.pull       = DISABLE;
	GPIO_InitStruct.remapPin   = DISABLE;	
	FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
    GPIO_InitStruct.pin        = FL_GPIO_PIN_3|FL_GPIO_PIN_9;
	GPIO_InitStruct.mode       = FL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.pull       = DISABLE;
	GPIO_InitStruct.remapPin   = DISABLE;	
	FL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void GPIO_ToggleBits(GPIO_Type* GPIOx, uint32_t GPIO_Pin)
{
	if(GPIO_Pin&GPIOx->DO)
	{
		FL_GPIO_ResetOutputPin(GPIOx,GPIO_Pin);	
	}
	else
	{	
        FL_GPIO_SetOutputPin(GPIOx,GPIO_Pin);
	}
}



