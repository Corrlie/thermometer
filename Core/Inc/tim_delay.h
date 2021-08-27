/*
 * tim_delay.h
 *
 *  Created on: Aug 27, 2021
 *      Author: hp
 */

#ifndef INC_TIM_DELAY_H_
#define INC_TIM_DELAY_H_

#include "tim.h"

void custom_delay_us(TIM_HandleTypeDef *htim_delay, uint32_t us);

#endif /* INC_TIM_DELAY_H_ */
