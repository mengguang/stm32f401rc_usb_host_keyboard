/*
 * misc_utils.h
 *
 *  Created on: Feb 26, 2019
 *      Author: mengguang
 */

#ifndef MISC_UTILS_H_
#define MISC_UTILS_H_

//#include "printf.h"
#include "stdio.h"

#include "string.h"
#include "main.h"
#include "gpio.h"
#include "stdint.h"
#include "stdbool.h"

#define HIGH	1
#define LOW		0

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} gpio_t;

void delay(uint32_t ms);
void digitalWrite(gpio_t gpio, uint8_t val);
uint8_t digitalRead(gpio_t gpio);
void digitalToggle(gpio_t gpio);
void mcu_reset();
void hex_dump(const uint8_t *data, uint32_t length);
void hex2bin(const char *src, uint8_t *target);
uint32_t millis();
#endif /* MISC_UTILS_H_ */
