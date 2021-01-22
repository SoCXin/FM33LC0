#ifndef __USER_INIT_H__
#define __USER_INIT_H__

#include "main.h"
#ifndef MFANG
#include <stdio.h>
#endif


#ifndef MFANG

#define LED0_GPIO   GPIOC
#define LED0_PIN    FL_GPIO_PIN_0

#define LED0_ON()   FL_GPIO_ResetOutputPin(LED0_GPIO, LED0_PIN)
#define LED0_OFF()  FL_GPIO_SetOutputPin(LED0_GPIO, LED0_PIN)
#define LED0_TOG()  FL_GPIO_ToggleOutputPin(LED0_GPIO, LED0_PIN)

#endif

void UserInit(void);
void FoutInit(void);
void DelayUs(uint32_t count);
void DelayMs(uint32_t count);

#endif
