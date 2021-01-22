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
  * @brief  GPTIM0_TimerBase Initialization function
  * @param  void
  * @retval None
  */
void MF_GPTIM0_TimerBase_Init(void)
{

    /*IO CONFIG*/
    FL_GPTIM_InitTypeDef    TimerBaseInitStruct;

    TimerBaseInitStruct.prescaler = (uint16_t)0x0009;
    TimerBaseInitStruct.counterMode = FL_GPTIM_COUNTER_DIR_UP;
    TimerBaseInitStruct.autoReload = 0xFFFFU;
    TimerBaseInitStruct.autoReloadState = DISABLE;
    TimerBaseInitStruct.clockDivision = FL_GPTIM_CLK_DIVISION_DIV1;

    FL_GPTIM_Init(GPTIM0,&TimerBaseInitStruct );


    FL_GPTIM_EnableIT_Update(GPTIM0 );


    FL_GPTIM_EnableIT_CC(GPTIM0,FL_GPTIM_CHANNEL_1 );

    
}
 
/**
  * @brief  GPTIM0_SlaveMode Initialization function
  * @param  void
  * @retval None
  */
void MF_GPTIM0_SlaveMode_Init(void)
{

    /*IO CONFIG*/
    FL_GPTIM_SlaveInitTypeDef    SlaveModeInitStruct;

    SlaveModeInitStruct.ITRSourceGroup = 0;
    SlaveModeInitStruct.slaveMode = FL_GPTIM_SLAVE_MODE_TRGI_RISE_RST;
    SlaveModeInitStruct.triggerSrc = FL_GPTIM_TIM_TS_TI1FP1;
    SlaveModeInitStruct.triggerDelay = ENABLE;

    FL_GPTIM_SlaveMode_Init(GPTIM0,&SlaveModeInitStruct );

    
}
 
/**
  * @brief  GPTIM0_Channel1 Initialization function
  * @param  void
  * @retval None
  */
void MF_GPTIM0_Channel1_Init(void)
{

    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_GPTIM_IC_InitTypeDef    defaultInitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = DISABLE;
    GPIO_InitStruct.remapPin = ENABLE;

    FL_GPIO_Init( GPIOB, &GPIO_InitStruct );

    defaultInitStruct.captureState = ENABLE;
    defaultInitStruct.ICPolarity = FL_GPTIM_IC_POLARITY_NORMAL;
    defaultInitStruct.ICActiveInput = FL_GPTIM_CHANNEL_MODE_INPUT_NORMAL;
    defaultInitStruct.ICPrescaler = FL_GPTIM_IC_PSC_DIV1;
    defaultInitStruct.ICFilter = FL_GPTIM_IC_FILTER_DIV1;

    FL_GPTIM_IC_Init(GPTIM0,FL_GPTIM_CHANNEL_1,&defaultInitStruct );

    
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
     MF_GPTIM0_TimerBase_Init();
     MF_GPTIM0_SlaveMode_Init();
     MF_GPTIM0_Channel1_Init();

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
