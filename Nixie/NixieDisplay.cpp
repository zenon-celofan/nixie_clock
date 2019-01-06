#include <stdio.h>
#include <stdlib.h>
#include <NixieDisplay.h>
#include <NixieTube.h>
#include "Led.h"
#include "Rtc.h"

extern Rtc rtc;

NixieDisplay::NixieDisplay(void) {

	cut_rtc_leading_zero = true;
	auto_update_from_rtc = false;
	balance_mode_active = false;

	custom_numbers(0, 0, 0, 0);

	init_auto_refresh();

    turned_on = true;

} //NixieDisplay()


void NixieDisplay::turn_on(void) {

	turned_on = true;

} //turn_on()


void NixieDisplay::turn_off(void) {

	turned_on = false;

	for (uint8_t i = 0; i < NUMBER_OF_NIXIE_TUBES; i++) {
		nixie_tube[i].turn_off();
	}

} //turn_off()


void NixieDisplay::refresh(void) {
	if (turned_on == true) {
		for (uint8_t i = 0; i < NUMBER_OF_NIXIE_TUBES; i++) {
			if (digit_active_status[i] == true) {
				nixie_tube[i].display_digit(digit[i]);
			} else {
				nixie_tube[i].turn_off();
			}
		}
	}
} //refresh()


void NixieDisplay::init_auto_refresh(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    // if MCU frequency 72 MHz, prescaler of value 72 will make 1us counter steps
    timerInitStructure.TIM_Prescaler = 72;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 1000; // will get irq each 1ms on TIMx->CNT overflow
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &timerInitStructure);
    TIM_Cmd(TIM3, ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
    /*for more accuracy irq priority should be higher, but now its default*/
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x05;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    NVIC_Init(&NVIC_InitStruct);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
} //init_auto_refresh()


void NixieDisplay::show_current_time(void) {

	int temp_hours;
	int temp_minutes;

	temp_hours = rtc.get_hours();
	temp_minutes = rtc.get_minutes();

	//update display digits
	digit[0] = (uint8_t)  temp_hours / 10;
	if (digit[0] == 0
			&& cut_rtc_leading_zero
			&& auto_update_from_rtc == true) {
		digit[0] = 11;   // turn off digit
	}
	digit[1] = (uint8_t)  temp_hours % 10;
	digit[2] = (uint8_t)  temp_minutes / 10;
	digit[3] = (uint8_t)  temp_minutes % 10;

} //show_current_time()


void NixieDisplay::custom_numbers(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
	digit[0] = d0;
	digit[1] = d1;
	digit[2] = d2;
	digit[3] = d3;
} //custom_numbers()
