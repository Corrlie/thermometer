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
	custom_delay_us(htim_delay, 260);
	return is_present;
}

void write_1(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay){
	set_pin_as_output(port, chosen_pin);
	HAL_GPIO_WritePin(port, chosen_pin, GPIO_PIN_RESET);
	custom_delay_us(htim_delay, 1);
	set_pin_as_input(port, chosen_pin);
	custom_delay_us(htim_delay, 59);
}

void write_0(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay){
	set_pin_as_output(port, chosen_pin);
	HAL_GPIO_WritePin(port, chosen_pin, GPIO_PIN_RESET);
	custom_delay_us(htim_delay, 60);
	set_pin_as_input(port, chosen_pin);
}

void write_byte(uint8_t byte, GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay){
	set_pin_as_output(port, chosen_pin);
	for (int i = 0; i<8 ; i++){
		if((byte&(1<<i))==0){
			write_0(port, chosen_pin, htim_delay);
		}
		else{
			write_1(port, chosen_pin, htim_delay);
		}
	}
}

uint8_t read_byte(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay){
	uint8_t byte = 0;
	for(int i = 0; i<8;i++){
		set_pin_as_output(port, chosen_pin);
		HAL_GPIO_WritePin(port, chosen_pin, GPIO_PIN_RESET);
		custom_delay_us(htim_delay, 2);
		set_pin_as_input(port, chosen_pin);
//		byte |= HAL_GPIO_ReadPin(port, chosen_pin)<<i;
		if(HAL_GPIO_ReadPin(port, chosen_pin)){
			byte |= 1<<i;
		}
		custom_delay_us(htim_delay, 60);
	}
	return byte;
}

float current_temp_1_sensor(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay){
	  bool reset_ds_presence = is_ds_present(port, chosen_pin, htim_delay);
	  HAL_Delay(1);

	  write_byte(0xCC, port, chosen_pin, htim_delay);
	  write_byte(0x44, port, chosen_pin, htim_delay);
	  HAL_Delay(375);

	  reset_ds_presence = is_ds_present(port, chosen_pin, htim_delay);
	  HAL_Delay(1);
	  write_byte(0xCC, port, chosen_pin, htim_delay);
	  write_byte(0xBE, port, chosen_pin, htim_delay);

	  // 9 bits
	  uint8_t read_temp1 = read_byte(port, chosen_pin, htim_delay);
	  uint8_t read_temp2 = read_byte(port, chosen_pin, htim_delay);
	  int temp_raw = (read_temp2<<8)|read_temp1;
	  float temp = (float)temp_raw*0.0625;
	  return temp;
}
