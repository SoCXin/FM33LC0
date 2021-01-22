/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : mf_config.c
  * @brief          : MCU FUNCTION CONFIG
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

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"

/* Private function prototypes -----------------------------------------------*/

 
/**
  * @brief  ADC_Common Initialization function
  * @param  void
  * @retval None
  */
void MF_ADC_Common_Init(void)
{

    /*IO CONFIG*/
    FL_ADC_CommonInitTypeDef    CommonInitStruct;

    CommonInitStruct.clockSource = FL_RCC_ADC_CLK_SOURCE_RCHF;
    CommonInitStruct.clockPrescaler = FL_RCC_ADC_PSC_DIV8;

    FL_ADC_CommonInit(&CommonInitStruct );

    
}
 
/**
  * @brief  ADC Initialization function
  * @param  void
  * @retval None
  */
void MF_ADC_Init(void)
{

    /*IO CONFIG*/
    FL_ADC_InitTypeDef    defaultInitStruct;

    defaultInitStruct.conversionMode = FL_ADC_CONV_MODE_SINGLE;
    defaultInitStruct.autoMode = FL_ADC_SINGLE_CONV_MODE_AUTO;
    defaultInitStruct.waitMode = ENABLE;
    defaultInitStruct.overrunMode = ENABLE;
    defaultInitStruct.scanDirection = FL_ADC_SEQ_SCAN_DIR_BACKWARD;
    defaultInitStruct.externalTrigConv = FL_ADC_TRIGGER_EDGE_NONE;
    defaultInitStruct.triggerSource = FL_ADC_TRGI_PA8;
    defaultInitStruct.fastChannelTime = FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK;
    defaultInitStruct.lowChannelTime = FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK;
    defaultInitStruct.oversamplingMode = ENABLE;
    defaultInitStruct.overSampingMultiplier = FL_ADC_OVERSAMPLING_MUL_16X;
    defaultInitStruct.oversamplingShift = FL_ADC_OVERSAMPLING_SHIFT_4B;

    FL_ADC_Init(ADC,&defaultInitStruct );

    
}


/**
  * @brief  The application entry point.
  * @retval int
  */
void MF_Clock_Init(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* System interrupt init*/

  /* Initialize all configured peripherals */
 
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void MF_SystemClock_Config(void)
{
 
}

void MF_Config_Init(void)
{
    /*FUNCTION CALL*/
     MF_ADC_Common_Init();
     MF_ADC_Init();

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
