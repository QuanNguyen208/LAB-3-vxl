/*
 * input_processing.c
 *
 *  Created on: Nov 24, 2022
 *      Author: Admin
 */


#include "main.h"
#include "input_reading.h"
#include "timer.h"
#include "led_control.h"
#include "traffic_light.h"

#define		BUTTON1 			0
#define		BUTTON2 			1
#define 	BUTTON3 			2
#define 	BUTTON4 			3

#define 	NUMBER_OF_MODES		4

#define 	MAX_CNT 			99
#define		MIN_CNT				1
#define		RED_INITIAL			0
#define		YEL_INITIAL			0
#define 	GRE_INITIAL			0

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState button1_state = BUTTON_RELEASED;
enum ButtonState button2_state = BUTTON_RELEASED;
enum ButtonState button3_state = BUTTON_RELEASED;
enum ButtonState button4_state = BUTTON_RELEASED;

int 	mode		= 	0;
int 	red_cnt		= 	RED_INITIAL;
int 	yel_cnt		= 	YEL_INITIAL;
int		gre_cnt		= 	GRE_INITIAL;
int		red_temp 	=	RED_INITIAL;
int	 	yel_temp	= 	YEL_INITIAL;
int		gre_temp	= 	GRE_INITIAL;
int		mode1_sw	= 	0;

int red_updating(){ //update red
	return red_cnt;
}
int yel_updating(){	//update yellow
	return yel_cnt;
}
int gre_updating(){	//update green
	return gre_cnt;
}
int mode1_sw_updating(){ //update mode1
	return mode1_sw;
}

void fsm_for_input_processing_1(void){
	switch(button1_state){
	case BUTTON_RELEASED:
		if(is_button_pressed(BUTTON1)){ //press MODE button
					button1_state = BUTTON_PRESSED;
					mode++;
					if (mode > NUMBER_OF_MODES) mode = 1;
					// normal
					if (mode == 1){
						mode1_sw = 1;
					}
					// adjust red
					if (mode == 2){
						mode1_sw = 0;

						traffic_light_update1(0, 99, 99);
						traffic_light_update2(0, 99, 99);
						UpdateBuffer_7SEG_LEDS(2, red_cnt/10);
						UpdateBuffer_7SEG_LEDS(3, red_cnt%10);
						red_temp = red_cnt;
					}
					// adjust yel
					if (mode == 3){
						traffic_light_update1(99, 0, 99);
						traffic_light_update2(99, 0, 99);
						UpdateBuffer_7SEG_LEDS(2, yel_cnt/10);
						UpdateBuffer_7SEG_LEDS(3, yel_cnt%10);
						yel_temp = yel_cnt;
					}
					// adjust gre
					if (mode == 4){
						traffic_light_update1(99, 99, 0);
						traffic_light_update2(99, 99, 0);
						UpdateBuffer_7SEG_LEDS(2, gre_cnt/10);
						UpdateBuffer_7SEG_LEDS(3, gre_cnt%10);
						gre_temp = gre_cnt;
					}
					UpdateBuffer_7SEG_LEDS(1, mode);
					break;
	}
	case BUTTON_PRESSED:
			if (!is_button_pressed(BUTTON1))
				button1_state = BUTTON_RELEASED;
			else
				if(is_button_pressed_1s(BUTTON1))
					button1_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed (BUTTON1)) {
				button1_state = BUTTON_RELEASED;
			}
			// todo

			break;

	}
}

void fsm_for_input_processing_2(void){
	switch (button2_state){
	case BUTTON_RELEASED:
		if(is_button_pressed(BUTTON2)){
			button2_state = BUTTON_PRESSED;
			if (mode == 2){
				if (++red_temp > MAX_CNT) red_temp = MIN_CNT;
				UpdateBuffer_7SEG_LEDS(3, red_temp%10);
				UpdateBuffer_7SEG_LEDS(2, red_temp/10);
			}
			if (mode == 3){
				if (++yel_temp > MAX_CNT) yel_temp = MIN_CNT;
				UpdateBuffer_7SEG_LEDS(3, yel_temp%10);
				UpdateBuffer_7SEG_LEDS(2, yel_temp/10);
			}
			if (mode == 4){
				if (++gre_temp > MAX_CNT) gre_temp = MIN_CNT;
				UpdateBuffer_7SEG_LEDS(3, gre_temp%10);
				UpdateBuffer_7SEG_LEDS(2, gre_temp/10);
			}
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(BUTTON2))
			button2_state = BUTTON_RELEASED;
		else
			if(is_button_pressed_1s(BUTTON2))
				button2_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed (BUTTON2)) {
			button2_state = BUTTON_RELEASED;
		}
		// todo

		break;
	}
}

void fsm_for_input_processing_3(void){
	switch (button3_state){
	case BUTTON_RELEASED:
		if(is_button_pressed(BUTTON3)){
			button3_state = BUTTON_PRESSED;
			if (mode == 2){
				if (red_temp == 0 || --red_temp < MIN_CNT) red_temp = MAX_CNT;
				UpdateBuffer_7SEG_LEDS(3, red_temp%10);
				UpdateBuffer_7SEG_LEDS(2, red_temp/10);
			}
			if (mode == 3){
				if (yel_temp == 0 || --yel_temp < MIN_CNT) yel_temp = MAX_CNT;
				UpdateBuffer_7SEG_LEDS(3, yel_temp%10);
				UpdateBuffer_7SEG_LEDS(2, yel_temp/10);
			}
			if (mode == 4){
				if (gre_temp == 0 || --gre_temp < MIN_CNT) gre_temp = MAX_CNT;
				UpdateBuffer_7SEG_LEDS(3, gre_temp%10);
				UpdateBuffer_7SEG_LEDS(2, gre_temp/10);
			}
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(BUTTON3))
			button3_state = BUTTON_RELEASED;
		else
			if(is_button_pressed_1s(BUTTON3))
				button3_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed (BUTTON3)) {
			button3_state = BUTTON_RELEASED;
		}
		// todo

		break;
	}
}

void fsm_for_input_processing_4(void){
	switch (button4_state){
	case BUTTON_RELEASED:
		if(is_button_pressed(BUTTON4)){
			button4_state = BUTTON_PRESSED;
			if (mode == 2){
				red_cnt = red_temp;
			}
			if (mode == 3){
				yel_cnt = yel_temp;
			}
			if (mode == 4){
				gre_cnt = gre_temp;
			}
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(BUTTON4))
			button4_state = BUTTON_RELEASED;
		else
			if(is_button_pressed_1s(BUTTON4))
				button4_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed (BUTTON4)) {
			button4_state = BUTTON_RELEASED;
		}
		// todo

		break;
	}
}
