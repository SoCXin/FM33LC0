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
  * @brief  U7816 Initialization function
  * @param  void
  * @retval None
  */
void MF_U7816_Init(void)
{

    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_U7816_InitTypeDef    defaultInitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    GPIO_InitStruct.remapPin = DISABLE;

    FL_GPIO_Init( GPIOC, &GPIO_InitStruct );

    GPIO_InitStruct.pin = FL_GPIO_PIN_12;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    GPIO_InitStruct.remapPin = DISABLE;

    FL_GPIO_Init( GPIOC, &GPIO_InitStruct );

    defaultInitStruct.baud = 371;
    defaultInitStruct.blockGuard = DISABLE;
    defaultInitStruct.strongPullUp = ENABLE;
    defaultInitStruct.errorGuardTime = FL_U7816_ERROR_GUARD_TIME_1ETU;
    defaultInitStruct.errorSignalWidth = FL_U7816_ERROR_SIGNAL_WIDTH_2ETU;
    defaultInitStruct.extraGuardTime = 0;
    defaultInitStruct.outputClockFreqence = 4000000;
    defaultInitStruct.rxAutoErrorSignal = ENABLE;
    defaultInitStruct.parity = FL_U7816_PARITY_EVEN;
    defaultInitStruct.txAutoRetry = ENABLE;
    defaultInitStruct.retryCnt = FL_U7816_RETRY_COUNT_1;
    defaultInitStruct.rxGuardTime = FL_U7816_RX_GUARD_TIME_2ETU;
    defaultInitStruct.txGuardTime = FL_U7816_TX_GUARD_TIME_2ETU;
    defaultInitStruct.transferOrder = FL_U7816_BIT_ORDER_LSB_FIRST;

    FL_U7816_Init(U7816,&defaultInitStruct );


    FL_U7816_EnableIT_RXComplete(U7816 );


    FL_U7816_EnableIT_TXComplete(U7816 );

    
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
     MF_U7816_Init();

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
