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
  * @brief  UART0 Initialization function
  * @param  void
  * @retval None
  */
void MF_UART0_Init(void)
{

    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_UART_InitTypeDef    defaultInitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_3;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    GPIO_InitStruct.remapPin = DISABLE;

    FL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    defaultInitStruct.clockSrc = FL_RCC_UART0_CLK_SOURCE_APB1CLK;
    defaultInitStruct.baudRate = 115200;
    defaultInitStruct.dataWidth = FL_UART_DATA_WIDTH_8B;
    defaultInitStruct.stopBits = FL_UART_STOP_BIT_WIDTH_1B;
    defaultInitStruct.parity = FL_UART_PARITY_EVEN;
    defaultInitStruct.transferDirection = FL_UART_DIRECTION_TX;

    FL_UART_Init(UART0,&defaultInitStruct );

    
}
 
/**
  * @brief  DMA_Channel2 Initialization function
  * @param  void
  * @retval None
  */
void MF_DMA_Channel2_Init(void)
{

    /*IO CONFIG*/
    FL_DMA_InitTypeDef    defaultInitStruct;

    defaultInitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION2;
    defaultInitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;
    defaultInitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
    defaultInitStruct.flashAddressIncMode = FL_DMA_CH7_FLASH_INC_MODE_INCREASE;
    defaultInitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
    defaultInitStruct.priority = FL_DMA_PRIORITY_HIGH;
    defaultInitStruct.circMode = DISABLE;

    FL_DMA_Init(DMA,&defaultInitStruct,FL_DMA_CHANNEL_2 );

    
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
     MF_UART0_Init();
     MF_DMA_Channel2_Init();

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
