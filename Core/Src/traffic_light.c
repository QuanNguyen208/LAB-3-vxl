/*
 * traffic_light.c
 *
 *  Created on: Nov 13, 2022
 *      Author: Admin
 */

#include "main.h"
#include "timer.h"
#include "led_control.h"
#include "traffic_light.h"

enum LightState {RED, YEL, GRE};
enum LightState lightstate_v = RED; //light state of vertical traffic light
enum LightState	lightstate_h = GRE; //horizontal light

void traffic_light_init(void){
	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
	HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 1);
	HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 1);
	HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
	HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 1);
	HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 1);
}

// vertical
void traffic_light_update1(int red_cnt, int yel_cnt, int gre_cnt){
	static int time_in_state = 0;

	if (red_cnt == 0 && yel_cnt == 0 && gre_cnt == 0) //back to init state
		traffic_light_init();

	// mode: normal
	else if (red_cnt > 0 && yel_cnt > 0 && gre_cnt > 0){ //press increase button red_cnt > 0
		switch (lightstate_v){
			case RED:
				HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 0);
				HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 1);
				HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 1);

				UpdateBuffer_7SEG_LEDS(0, (red_cnt - time_in_state)/10);
				UpdateBuffer_7SEG_LEDS(1, (red_cnt - time_in_state)%10);
				if (++time_in_state == red_cnt){ //time_in_state+1 == red_cnt
					lightstate_v = GRE;
					time_in_state = 0;
				}
				break;
			case YEL:
				HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
				HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 0);
				HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 1);

				UpdateBuffer_7SEG_LEDS(0, (yel_cnt - time_in_state)/10);
				UpdateBuffer_7SEG_LEDS(1, (yel_cnt - time_in_state)%10);
				if (++time_in_state == yel_cnt){
					lightstate_v = RED;
					time_in_state = 0;
				}
				break;
			case GRE:
				HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
				HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 1);
				HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 0);

				UpdateBuffer_7SEG_LEDS(0, (gre_cnt - time_in_state)/10);
				UpdateBuffer_7SEG_LEDS(1, (gre_cnt - time_in_state)%10);
				if (++time_in_state == gre_cnt){
					lightstate_v = YEL;
					time_in_state = 0;
				}
				break;
		}
	}

	// mode: adjust
	else { //when red_cnt == 0 turn on red
		if (red_cnt == 0) {
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 0);
			HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 1);
			HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 1);
		}
		if (yel_cnt == 0) {
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
			HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 0);
			HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 1);
		}
		if (gre_cnt == 0) {
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
			HAL_GPIO_WritePin(YEL_1_GPIO_Port, YEL_1_Pin, 1);
			HAL_GPIO_WritePin(GRE_1_GPIO_Port, GRE_1_Pin, 0);
		}
	}
}

// horizontal
void traffic_light_update2(int red_cnt, int yel_cnt, int gre_cnt){
	static int time_in_state = 0;

	if (red_cnt == 0 && yel_cnt == 0 && gre_cnt == 0)
		traffic_light_init();

	// mode: normal
	else if (red_cnt > 0 && yel_cnt > 0 && gre_cnt > 0){
		switch (lightstate_h){
			case RED:
				HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 0);
				HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 1);
				HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 1);

				UpdateBuffer_7SEG_LEDS(2, (red_cnt - time_in_state)/10);
				UpdateBuffer_7SEG_LEDS(3, (red_cnt - time_in_state)%10);
				if (++time_in_state == red_cnt){
					lightstate_h = GRE;
					time_in_state = 0;
				}
				break;
			case YEL:
				HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
				HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 0);
				HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 1);

				UpdateBuffer_7SEG_LEDS(2, (yel_cnt - time_in_state)/10);
				UpdateBuffer_7SEG_LEDS(3, (yel_cnt - time_in_state)%10);
				if (++time_in_state == yel_cnt){
					lightstate_h = RED;
					time_in_state = 0;
				}
				break;
			case GRE:
				HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
				HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 1);
				HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 0);

				UpdateBuffer_7SEG_LEDS(2, (gre_cnt - time_in_state)/10);
				UpdateBuffer_7SEG_LEDS(3, (gre_cnt - time_in_state)%10);
				if (++time_in_state == gre_cnt){
					lightstate_h = YEL;
					time_in_state = 0;
				}
				break;
		}
	}

	// mode: adjust
	else {
		if (red_cnt == 0) {
			HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 0);
			HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 1);
			HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 1);
		}
		if (yel_cnt == 0) {
			HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
			HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 0);
			HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 1);
		}
		if (gre_cnt == 0) {
			HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
			HAL_GPIO_WritePin(YEL_2_GPIO_Port, YEL_2_Pin, 1);
			HAL_GPIO_WritePin(GRE_2_GPIO_Port, GRE_2_Pin, 0);
		}
	}
}
