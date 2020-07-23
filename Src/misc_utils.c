/*
 * misc_utils.c
 *
 *  Created on: Feb 26, 2019
 *      Author: mengguang
 */

#include "misc_utils.h"
#include "usart.h"

//void _putchar(char c) {
//	HAL_UART_Transmit(&huart1, (uint8_t *)&c, 1, 10);
//}

int _write(int file, char *ptr, int len) {
	(void) file; /* Not used, avoid warning */
	HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, 1000);
	return len;
}

void digitalWrite(gpio_t gpio, uint8_t val) {
	if (val == HIGH) {
		HAL_GPIO_WritePin(gpio.port, gpio.pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(gpio.port, gpio.pin, GPIO_PIN_RESET);
	}
}

void digitalToggle(gpio_t gpio) {
	if (digitalRead(gpio) == HIGH) {
		digitalWrite(gpio, LOW);
	} else {
		digitalWrite(gpio, HIGH);
	}
}

uint8_t digitalRead(gpio_t gpio) {
	GPIO_PinState ps;
	ps = HAL_GPIO_ReadPin(gpio.port, gpio.pin);
	if (ps == GPIO_PIN_SET) {
		return HIGH;
	} else {
		return LOW;
	}
}

void delay(uint32_t ms) {
	HAL_Delay(ms);
}

void mcu_reset() {
	printf("Reset MCU.\r\n");
	delay(1000);
	NVIC_SystemReset();
}

void hex_dump(const uint8_t *data, uint32_t length) {
	if(length > 16) {
		length = 16;
	}
	for (int i = 0; i < length; i++) {
		printf("%02X ", data[i]);
		if ((i + 1) % 16 == 0) {
			printf("\r\n");
		}
	}
	if (length % 16 != 0) {
		printf("\r\n");
	}
}

uint32_t millis() {
	return HAL_GetTick();
}

int char2int(char input) {
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	return 0;
}

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large
void hex2bin(const char *src, uint8_t *target) {
	while (*src && src[1]) {
		*(target++) = char2int(*src) * 16 + char2int(src[1]);
		src += 2;
	}
}


