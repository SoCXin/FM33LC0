/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fm33lc0xx_fl_rcc.h"
#include "fm33lc0xx_fl_lptim32.h"
#include "fm33lc0xx_fl_lpuart.h"
#include "fm33lc0xx_fl_gpio.h"
#include "fm33lc0xx_fl_uart.h"
#include "fm33lc0xx_fl_vref.h"
#include "fm33lc0xx_fl_iwdt.h"
#include "fm33lc0xx_fl_wwdt.h"
#include "fm33lc0xx_fl_pmu.h"
#include "fm33lc0xx_fl_flash.h"
#include "fm33lc0xx_fl_svd.h"
#include "fm33lc0xx_fl_aes.h"
#include "fm33lc0xx_fl_rmu.h"
#include "fm33lc0xx_fl_rng.h"
#include "fm33lc0xx_fl_opa.h"
#include "fm33lc0xx_fl_comp.h"
#include "fm33lc0xx_fl_divas.h"
#include "fm33lc0xx_fl_i2c.h"
#include "fm33lc0xx_fl_spi.h"
#include "fm33lc0xx_fl_u7816.h"
#include "fm33lc0xx_fl_bstim32.h"
#include "fm33lc0xx_fl_gptim.h"
#include "fm33lc0xx_fl_atim.h"
#include "fm33lc0xx_fl_crc.h"
#include "fm33lc0xx_fl_dma.h"
#include "fm33lc0xx_fl_rtc.h"
#include "fm33lc0xx_fl_lcd.h"
#include "mf_config.h"


#if defined(USE_FULL_ASSERT)
#include "fm33_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
