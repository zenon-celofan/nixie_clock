#include <NixieDisplay.h>
#include "IRQHandler.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rtc.h"
//#include "Neo6M.h"
#include "serial2.h"
#include "Led.h"
#include "Relay.h"
#include "bluepill.h"
#include <stdio.h>
#include <stdlib.h>

extern uint32_t milliseconds_after_reset;
extern NixieDisplay nixie_display;
extern char esp8266_rx_frame[];


//nixie display refresh
void TIM3_IRQHandler(void) {

	static uint8_t current_digit = 0;

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

	if (nixie_display.auto_update_from_rtc == true) {
		nixie_display.show_current_time();
	} else if (nixie_display.balance_mode_active == true) {
		//nixie_display.digit[current_digit] > 9 ? nixie_display.digit[current_digit] = 0 : nixie_display.digit[current_digit] += 1;
		nixie_display.digit[current_digit] += 1;
		if (nixie_display.digit[current_digit] > 9) {
			nixie_display.digit[current_digit] = 0;
		}
	}

	nixie_display.digit_active_status[current_digit] = false;

	current_digit++;
	current_digit = current_digit % NUMBER_OF_NIXIE_TUBES;

	nixie_display.digit_active_status[current_digit] = true;

	nixie_display.refresh();

} //TIM3_IRQHandler


//millis() counter
void TIM4_IRQHandler(void) {

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

	milliseconds_after_reset++;

} //TIM4_IRQHandler


void EXTI0_IRQHandler(void) {
} //EXTI0_IRQHandler();


void EXTI15_10_IRQHandler(void) {
} //EXTI15_10_IRQHandler();


//clock source receive frame
void USART3_IRQHandler(void) {

    static char rx_frame[RX_FRAME_SIZE];
	static uint8_t byte_position_in_frame = 0;

	uint16_t received_byte;
	int temp_hours;
	int temp_minutes;
	int temp_seconds;

    if ((USART3->SR & USART_FLAG_IDLE) != 0) {
    	received_byte = (uint8_t) USART3->SR;         // Clear IDLE flag by reading status register first, and follow by reading data register
    	received_byte = (uint8_t) USART3->DR;
    	byte_position_in_frame = 0;
    	USART_ITConfig(USART3, USART_IT_IDLE, DISABLE);
    } else {
    	received_byte = (uint8_t) USART3->DR;
    	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

    	if (received_byte == RX_FRAME_START_BYTE) {
			byte_position_in_frame = 0;
		}

		rx_frame[byte_position_in_frame] = (char) received_byte;
		byte_position_in_frame++;
		if (byte_position_in_frame >= RX_FRAME_SIZE) {
			byte_position_in_frame = 0;
		}

		if (received_byte == RX_FRAME_END_BYTE) {
			received_byte = 0;
			byte_position_in_frame = 0;
			if (index_of(rx_frame, "!", 0) == 0) {
				uint8_t pos = 0;
				do {
					esp8266_rx_frame[pos] = rx_frame[pos];
				} while (rx_frame[pos++] != RX_FRAME_END_BYTE);
					sscanf(esp8266_rx_frame, "!%2d:%2d:%2d", &temp_hours, &temp_minutes, &temp_seconds);
					RTC_SetCounter((uint32_t) temp_hours * 3600 + temp_minutes * 60 + temp_seconds);
			}
		}
    }
} //USART3_IRQHandler()
