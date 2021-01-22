#ifndef __GPIO_H__
#define __GPIO_H__

#include "fm33lc0xx_fl_gpio.h"

/*功能IO宏定义*/
#define LED1_GPIO		GPIOC
#define LED1_PIN		FL_GPIO_PIN_1

#define LED2_GPIO		GPIOA
#define LED2_PIN		FL_GPIO_PIN_5

#define LED3_GPIO		GPIOA
#define LED3_PIN		FL_GPIO_PIN_6

#define LED4_GPIO		GPIOA
#define LED4_PIN		FL_GPIO_PIN_7

/*操作宏定义*/
#define LED1_ON			FL_GPIO_ResetOutputPin(LED1_GPIO, LED1_PIN);
#define LED1_OFF		FL_GPIO_SetOutputPin(LED1_GPIO, LED1_PIN)
#define LED1_TOG		GPIO_ToggleBits(LED1_GPIO, LED1_PIN)

#define LED2_ON			FL_GPIO_ResetOutputPin(LED2_GPIO, LED2_PIN)
#define LED2_OFF		FL_GPIO_SetOutputPin(LED2_GPIO, LED2_PIN)
#define LED2_TOG		GPIO_ToggleBits(LED2_GPIO, LED2_PIN)

#define LED3_ON			FL_GPIO_ResetOutputPin(LED3_GPIO, LED3_PIN)
#define LED3_OFF		FL_GPIO_SetOutputPin(LED3_GPIO, LED3_PIN)
#define LED3_TOG		GPIO_ToggleBits(LED3_GPIO, LED3_PIN)

#define LED4_ON			FL_GPIO_ResetOutputPin(LED4_GPIO, LED4_PIN)
#define LED4_OFF		FL_GPIO_SetOutputPin(LED4_GPIO, LED4_PIN)
#define LED4_TOG		GPIO_ToggleBits(LED4_GPIO, LED4_PIN)

extern void GPIO_Init(void);
extern void GPIO_ToggleBits(GPIO_Type* GPIOx, uint32_t GPIO_Pin);
#endif
