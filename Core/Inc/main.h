/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
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
#include "stm32f1xx_hal.h"

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
#define BUT_1_Pin GPIO_PIN_0
#define BUT_1_GPIO_Port GPIOA
#define BUT_2_Pin GPIO_PIN_1
#define BUT_2_GPIO_Port GPIOA
#define BUT_3_Pin GPIO_PIN_2
#define BUT_3_GPIO_Port GPIOA
#define BUT_4_Pin GPIO_PIN_3
#define BUT_4_GPIO_Port GPIOA
#define RED_1_Pin GPIO_PIN_5
#define RED_1_GPIO_Port GPIOA
#define YEL_1_Pin GPIO_PIN_6
#define YEL_1_GPIO_Port GPIOA
#define GRE_1_Pin GPIO_PIN_7
#define GRE_1_GPIO_Port GPIOA
#define LED7_B_Pin GPIO_PIN_10
#define LED7_B_GPIO_Port GPIOB
#define LED7_C_Pin GPIO_PIN_11
#define LED7_C_GPIO_Port GPIOB
#define LED7_D_Pin GPIO_PIN_12
#define LED7_D_GPIO_Port GPIOB
#define LED7_E_Pin GPIO_PIN_13
#define LED7_E_GPIO_Port GPIOB
#define LED7_F_Pin GPIO_PIN_14
#define LED7_F_GPIO_Port GPIOB
#define LED7_G_Pin GPIO_PIN_15
#define LED7_G_GPIO_Port GPIOB
#define RED_2_Pin GPIO_PIN_8
#define RED_2_GPIO_Port GPIOA
#define YEL_2_Pin GPIO_PIN_9
#define YEL_2_GPIO_Port GPIOA
#define GRE_2_Pin GPIO_PIN_10
#define GRE_2_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_4
#define LED_1_GPIO_Port GPIOB
#define LED_2_Pin GPIO_PIN_5
#define LED_2_GPIO_Port GPIOB
#define LED_3_Pin GPIO_PIN_6
#define LED_3_GPIO_Port GPIOB
#define LED_4_Pin GPIO_PIN_7
#define LED_4_GPIO_Port GPIOB
#define LED7_A_Pin GPIO_PIN_9
#define LED7_A_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
