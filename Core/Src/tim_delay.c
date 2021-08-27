/*
 * tim_delay.c
 *
 *  Created on: Aug 27, 2021
 *      Author: hp
 */
#include "tim_delay.h"

void custom_delay_us(TIM_HandleTypeDef *htim_delay, uint32_t us){
	(htim_delay)->Instance->CNT = 0;
	while(__HAL_TIM_GET_COUNTER(htim_delay)<us);


}
