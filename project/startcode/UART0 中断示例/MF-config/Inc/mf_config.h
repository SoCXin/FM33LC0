/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : mf_config.h
  * @brief          : Header for mf_config.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) [2019] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under the Mulan PSL v1.
  * can use this software according to the terms and conditions of the Mulan PSL v1.
  * You may obtain a copy of Mulan PSL v1 at:
  * http://license.coscl.org.cn/MulanPSL
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
  * PURPOSE.
  * See the Mulan PSL v1 for more details.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MF_CONFIG_H
#define __MF_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_fl_adc.h"
#include "fm33lc0xx_fl_aes.h"
#include "fm33lc0xx_fl_atim.h"
#include "fm33lc0xx_fl_bstim32.h"
#include "fm33lc0xx_fl_comp.h"
#include "fm33lc0xx_fl_crc.h"
#include "fm33lc0xx_fl_dma.h"
#include "fm33lc0xx_fl_flash.h"
#include "fm33lc0xx_fl_gpio.h"
#include "fm33lc0xx_fl_gptim.h"
#include "fm33lc0xx_fl_divas.h"
#include "fm33lc0xx_fl_i2c.h"
#include "fm33lc0xx_fl_iwdt.h"
#include "fm33lc0xx_fl_lptim32.h"
#include "fm33lc0xx_fl_lpuart.h"
#include "fm33lc0xx_fl_opa.h"
#include "fm33lc0xx_fl_pmu.h"
#include "fm33lc0xx_fl_rcc.h"
#include "fm33lc0xx_fl_rng.h"
#include "fm33lc0xx_fl_rtc.h"
#include "fm33lc0xx_fl_spi.h"
#include "fm33lc0xx_fl_svd.h"
#include "fm33lc0xx_fl_u7816.h"
#include "fm33lc0xx_fl_uart.h"
#include "fm33lc0xx_fl_wwdt.h"
#include "fm33lc0xx_fl_lcd.h"
#include "fm33lc0xx_fl_vref.h"
#include "fm33lc0xx_fl_rmu.h"


#if defined(USE_FULL_ASSERT)
#include "fm33_assert.h"
#endif /* USE_FULL_ASSERT */

#ifdef MFANG
#include "user_init.h"
#endif
/* Exported functions prototypes ---------------------------------------------*/
void MF_Clock_Init(void);
void MF_SystemClock_Config(void);
void MF_Config_Init(void);
void Error_Handler(void);
void MF_PMU_Init(void);


/* Private defines -----------------------------------------------------------*/

#ifndef NVIC_PRIORITYGROUP_0

#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif


#ifdef __cplusplus
}
#endif

#endif /* __MF_CONFIG_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
