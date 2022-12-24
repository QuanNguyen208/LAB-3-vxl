/*
 * led_control.h
 *
 *  Created on: Nov 18, 2022
 *      Author: Admin
 */

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_

#define TIMER_CYCLE 10
#define NUMBER_OF_TIMER 3

void UpdateBuffer_7SEG_LEDS(uint8_t idx, uint8_t val);
void ClearPrevious_7SEG_LEDS(uint8_t index);
void Display_7SEG_DATA(uint8_t val);
void SetCurrent_7SEG_LEDS(uint8_t index);
void Driver_7SEG_LEDS(void);


#endif /* INC_LED_CONTROL_H_ */
