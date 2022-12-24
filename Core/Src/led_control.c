/*
 * led_control.c
 *
 *  Created on: Nov 13, 2022
 *      Author: Admin
 */

#include "main.h"
#include "led_control.h"

#define NUMBER_OF_DECIMAL_DIGITS	10
#define	NUMBER_OF_7SEG_LEDS			4

// common anode

// common Anode
static uint8_t Conversion_7SEG_LEDS[NUMBER_OF_DECIMAL_DIGITS] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};// binary to hexa //nhan dien

static uint8_t Buffer_7SEG_LEDS[NUMBER_OF_7SEG_LEDS];

static uint16_t ControlPin_7SEG_LEDs[NUMBER_OF_7SEG_LEDS] = {
		LED_1_Pin,
		LED_2_Pin,
		LED_3_Pin,
		LED_4_Pin,
};

static GPIO_TypeDef * ControlPort_7SEG_LEDs[NUMBER_OF_7SEG_LEDS] = {
		LED_1_GPIO_Port,
		LED_2_GPIO_Port,
		LED_3_GPIO_Port,
		LED_4_GPIO_Port,
};

static uint16_t DataPin_7SEG_LEDS[7] = {
		LED7_A_Pin,
		LED7_B_Pin,
		LED7_C_Pin,
		LED7_D_Pin,
		LED7_E_Pin,
		LED7_F_Pin,
		LED7_G_Pin,
};

static GPIO_TypeDef * DataPort_7SEG_LEDS[7] = {
		LED7_A_GPIO_Port,
		LED7_B_GPIO_Port,
		LED7_C_GPIO_Port,
		LED7_D_GPIO_Port,
		LED7_E_GPIO_Port,
		LED7_F_GPIO_Port,
		LED7_G_GPIO_Port,
};

void UpdateBuffer_7SEG_LEDS(uint8_t idx, uint8_t val){
	//update value
	if(idx < NUMBER_OF_7SEG_LEDS && val < NUMBER_OF_DECIMAL_DIGITS )
	Buffer_7SEG_LEDS[idx] = val;
}

void ClearPrevious_7SEG_LEDS(uint8_t index){// tat den
	if(index < NUMBER_OF_7SEG_LEDS)
	HAL_GPIO_WritePin(ControlPort_7SEG_LEDs[index], ControlPin_7SEG_LEDs[index], 1);
}

void Display_7SEG_DATA(uint8_t val){
	uint8_t idx;
	for(idx = 0; idx < 7; idx++){
		if((val>>idx) & 0x01){ //hexa ve binary thanh chuoi //so voi 0x01
			HAL_GPIO_WritePin(DataPort_7SEG_LEDS[idx], DataPin_7SEG_LEDS[idx], 0);
		} else {
			HAL_GPIO_WritePin(DataPort_7SEG_LEDS[idx], DataPin_7SEG_LEDS[idx], 1);
		}
	}
}

void SetCurrent_7SEG_LEDS(uint8_t index){// current led
	if(index >= NUMBER_OF_7SEG_LEDS) return;
	HAL_GPIO_WritePin(ControlPort_7SEG_LEDs[index], ControlPin_7SEG_LEDs[index], 0);
}

void Driver_7SEG_LEDS(void){// run all previous function
	static uint8_t ledIndex = 0;
	ClearPrevious_7SEG_LEDS(ledIndex);
	ledIndex = (ledIndex + 1)%NUMBER_OF_7SEG_LEDS;
	Display_7SEG_DATA(Conversion_7SEG_LEDS[Buffer_7SEG_LEDS[ledIndex]]);
	SetCurrent_7SEG_LEDS(ledIndex);
}
