/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : gpio_interrupt.h
  * @brief          : Header for gpio_interrupt.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 FMSH.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by FM under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_INTERRUPT_H
#define __GPIO_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


void GPIO_interrupt_init(void);// 外部引脚中断初始化



#ifdef __cplusplus
}
#endif

#endif /* __GPIO_INTERRUPT_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
