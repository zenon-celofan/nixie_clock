#include "bluepill.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include <stdio.h>
#include <string.h>

uint32_t milliseconds_after_reset = 0;


uint16_t index_of(const char * str1, const char * str2, uint16_t starting_from_index ) {

	uint16_t len = strlen(str1);
	uint16_t return_value;



	if (starting_from_index < len) {

		char * found = strstr(str1 + starting_from_index, str2);

		if (found != NULL) {
			return_value = found - str1;
		} else return_value = len;

	} else return_value = len;

	return return_value;

} //index_of()


GPIO_TypeDef * get_pin_port(uint8_t pin) {

	GPIO_TypeDef * pin_port;

	pin = pin >> 4;

	if (pin == 0) {
		pin_port = GPIOA;
	} else if (pin == 1) {
		pin_port = GPIOB;
	} else {
		pin_port = GPIOC;
	}

	return pin_port;

} //pin_port()


uint16_t get_pin_number(uint8_t pin) {

	uint16_t pin_number;
	const uint8_t PIN_NUMBER_MASK = 0b00001111;

	pin = pin & PIN_NUMBER_MASK;

	if (pin == 0) {
		pin_number = GPIO_Pin_0;
	} else 	if (pin == 1) {
		pin_number = GPIO_Pin_1;
	} else 	if (pin == 2) {
		pin_number = GPIO_Pin_2;
	} else 	if (pin == 3) {
		pin_number = GPIO_Pin_3;
	} else 	if (pin == 4) {
		pin_number = GPIO_Pin_4;
	} else 	if (pin == 5) {
		pin_number = GPIO_Pin_5;
	} else 	if (pin == 6) {
		pin_number = GPIO_Pin_6;
	} else 	if (pin == 7) {
		pin_number = GPIO_Pin_7;
	} else 	if (pin == 8) {
		pin_number = GPIO_Pin_8;
	} else 	if (pin == 9) {
		pin_number = GPIO_Pin_9;
	} else 	if (pin == 10) {
		pin_number = GPIO_Pin_10;
	} else 	if (pin == 11) {
		pin_number = GPIO_Pin_11;
	} else 	if (pin == 12) {
		pin_number = GPIO_Pin_12;
	} else 	if (pin == 13) {
		pin_number = GPIO_Pin_13;
	} else 	if (pin == 14) {
		pin_number = GPIO_Pin_14;
	} else 	if (pin == 15) {
		pin_number = GPIO_Pin_15;
	}

	return pin_number;

} //pin_port()


void millis_init(void) {

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    // if MCU frequency 72 MHz, prescaler of value 72 will make 1us counter steps
    timerInitStructure.TIM_Prescaler = 72;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 1000; // will get irq each 1ms on TIMx->CNT overflow
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &timerInitStructure);
    TIM_Cmd(TIM4, ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    /*for more accuracy irq priority should be higher, but now its default*/
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    NVIC_Init(&NVIC_InitStruct);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
} //millis_init()


uint32_t millis(void) {

	return milliseconds_after_reset;

} //millis()


uint8_t	check_parity(uint16_t integer) {

	uint8_t parity = 0;

	while (integer != 0) {
		parity += integer & 0x1;
		integer = integer >> 1;
	}

	parity %= 2;

	return parity;
}  //check_parity()
