/*
 * ds18b20.h
 *
 *  Created on: 27 sie 2021
 *      Author: hp
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include <stdbool.h>
#include "gpio.h"

void set_pin_as_input(GPIO_TypeDef *port, uint32_t chosen_pin);
void set_pin_as_output(GPIO_TypeDef *port, uint32_t chosen_pin);

bool is_ds_present(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay);

void write_1(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay);
void write_0(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay);

void write_byte(uint8_t byte, GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay);


uint8_t read_byte(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay);

float current_temp_1_sensor(GPIO_TypeDef *port, uint32_t chosen_pin, TIM_HandleTypeDef *htim_delay);

#endif /* INC_DS18B20_H_ */
