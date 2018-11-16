#include "pc13led.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void pc13led_init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void pc13led_on(void) {
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void pc13led_off(void) {
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}

void pc13led_toggle(void) {
	GPIOC->ODR ^= GPIO_Pin_13;
}

void pc13led_set(uint8_t state) {
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction) !state);
}
