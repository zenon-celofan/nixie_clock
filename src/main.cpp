#include <NixieDisplay.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "bluepill.h"
#include "delay.h"
#include "serial2.h"
#include "Led.h"
#include "Relay.h"
#include "Neo6M.h"
#include "Rtc.h"
#include "stm32f10x_rtc.h"
#include "Pin.h"

#define TIME_REFRESH_PERIOD_MS	1000

Pin		esp8266_pin(GPIOB, GPIO_Pin_1);
Neo6M 	gps_receiver;
NixieDisplay nixie_display;
Rtc 	rtc;
Led 	led_builtin(PC13, Bit_RESET);
Relay 	clicker_relay(PB1, Bit_RESET);
uint32_t time = 0;
char 	esp8266_rx_frame[100];
char 	gps_fix_status;
char 	temp_str[100];





void main() {

	esp8266_pin.digital_write(LOW);

	millis_init();

	serial2_init();			//debug serial
	serial2_send("\n\n\n*** nixie_clock - RESET ***\n\n");

    led_builtin.turn_off();

    time = millis();
    uint32_t RTC_Counter;

    //delay(3000);
    esp8266_pin.digital_write(HIGH);


    //while(1);

    while (1) {

		if ((millis() - time) > TIME_REFRESH_PERIOD_MS) {
			time = millis();
			if (esp8266_rx_frame[0] != 0) {
				serial2_send(esp8266_rx_frame);
				esp8266_rx_frame[0] = 0;
			}

			nixie_display.update_time();
			//nixie_display.custom_numbers(2,3,4,5);

			RTC_Counter = RTC_GetCounter() % 86400;
			sprintf(temp_str, "RTC time --%d:%d:%d--\n", (int) (RTC_Counter / 3600), (int) (RTC_Counter % 3600) / 60, (int) (RTC_Counter % 3600) % 60);
			serial2_send(temp_str);
		}

	}


} //main()


