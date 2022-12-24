/*
 * input_reading.c
 *
 *  Created on: Nov 13, 2022
 *      Author: Admin
 */

#include "main.h"

#define NUMBER_OF_BUTTONS 				4
#define DURATION_FOR_AUTO_INCREASING 	100
#define BUTTON_IS_PRESSED 				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 				GPIO_PIN_SET

static GPIO_PinState 	buttonBuffer 			[NUMBER_OF_BUTTONS];
static GPIO_PinState 	debounceButtonBuffer1 	[NUMBER_OF_BUTTONS];
static GPIO_PinState 	debounceButtonBuffer2 	[NUMBER_OF_BUTTONS];
static int   			flagForButtonPress1s 	[NUMBER_OF_BUTTONS];
static int 		counterForButtonPress1s [NUMBER_OF_BUTTONS];

static int ControlPin_BUTTONS[NUMBER_OF_BUTTONS] = {
		BUT_1_Pin,
		BUT_2_Pin,
		BUT_3_Pin,
		BUT_4_Pin,
};

static GPIO_TypeDef * ControlPort_BUTTONS[NUMBER_OF_BUTTONS] = {
		BUT_1_GPIO_Port,
		BUT_2_GPIO_Port,
		BUT_3_GPIO_Port,
		BUT_4_GPIO_Port,
};

void button_reading (void){
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(ControlPort_BUTTONS[i], ControlPin_BUTTONS[i]);
		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
			buttonBuffer[i] = debounceButtonBuffer1[i];
			if (buttonBuffer[i] == BUTTON_IS_PRESSED){
				if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
					counterForButtonPress1s[i]++;
				}
				else {
					flagForButtonPress1s[i] = 1;
				}
			}
			else {
				counterForButtonPress1s[i] = 0;
				flagForButtonPress1s[i] = 0;
			}
		}
	}
}

unsigned char is_button_pressed(int index){
	if (index >= NUMBER_OF_BUTTONS)
		return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(int index){
	if (index >= NUMBER_OF_BUTTONS)
		return 0;
	return (flagForButtonPress1s[index] == 1);
}
