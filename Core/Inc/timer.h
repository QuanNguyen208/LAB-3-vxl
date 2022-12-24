/*
 * timer.h
 *
 *  Created on: Nov 13, 2022
 *      Author: Admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define TIMER_CYCLE 10
#define NUMBER_OF_TIMER 3

int	timer_counter	[NUMBER_OF_TIMER];
int	timer_flag		[NUMBER_OF_TIMER];

void timer_set(int idx, int duration);
void timer_run(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIMER_H_ */
