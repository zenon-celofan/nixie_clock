#include <Pin.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

Pin::Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	GPIO = GPIOx;
	number = GPIO_Pin;
	//mode = GPIO_Mode_Out_PP;
	//speed = GPIO_Speed_2MHz;

	init_pin();
} //Pin


Pin::Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Pin_Mode) {
	GPIO = GPIOx;
	number = GPIO_Pin;
	mode = Pin_Mode;
	//speed = GPIO_Speed_2MHz;

	init_pin();
} //Pin

Pin::Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Pin_Mode, GPIOSpeed_TypeDef Pin_Speed) {
	GPIO = GPIOx;
	number = GPIO_Pin;
	mode = Pin_Mode;
	speed = Pin_Speed;

	init_pin();
} //Pin

void Pin::init_pin() {

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = number;
	GPIO_InitStructure.GPIO_Mode = mode;
	GPIO_InitStructure.GPIO_Speed = speed;

	if (GPIO == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if (GPIO == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if (GPIO == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_WriteBit(GPIO, number, Bit_RESET);

} //init_pin()


void Pin::digital_write(uint8_t new_state) {

	GPIO_WriteBit(GPIO, number, (BitAction) new_state);

} //digital_write

uint8_t Pin::digital_read(void) {

	return GPIO_ReadInputDataBit(GPIO, number);

} //digital_read

void Pin::digital_toggle(void) {

	GPIO->ODR ^= number;

} //digital_toggle
