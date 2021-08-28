/*
 * ds18b20.c
 *
 *  Created on: 27 sie 2021
 *      Author: hp
 */


#include "ds18b20.h"
#include "tim_delay.h"

void set_pin_as_input(GPIO_TypeDef *port, uint32_t chosen_pin){
	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.Pin = chosen_pin;
	gpio_init_struct.Mode = GPIO_MODE_INPUT;
	gpio_init_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port, &gpio_init_struct);
}

void set_pin_as_output(GPIO_TypeDef *port, uint32_t chosen_pin){
	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.Pin = chosen_pin;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD;
	gpio_init_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port, &gpio_init_struct);
}


bool is_ds_present(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay){
	bool is_present = false;
	set_pin_as_output(port, chosen_pin);
	HAL_GPIO_WritePin(port, chosen_pin, GPIO_PIN_RESET);
	custom_delay_us(htim_delay, 600);
	set_pin_as_input(port, chosen_pin);
	custom_delay_us(htim_delay, 100);
	if(!(HAL_GPIO_ReadPin(port, chosen_pin))){
		is_present = true;
	}
	return is_present;


}
