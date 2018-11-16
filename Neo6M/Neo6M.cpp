#include "Neo6M.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
//#include "stm32f10x_exti.h"
#include "bluepill.h"
#include "delay.h"
#include "serial3.h"

Neo6M::Neo6M(void) {

	current_time = (uint16_t) ((DEFAULT_HOURS_10 << 24) | (DEFAULT_HOURS_1 << 16) | (DEFAULT_MINUTES_10 << 8) | (DEFAULT_MINUTES_1));


	serial3_init();
	init_receive_interrupt();

} //Neo6M()


void Neo6M::init_receive_interrupt(void) {

	NVIC_InitTypeDef NVIC_InitStructure;

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

} //init_receive_interrupt()
