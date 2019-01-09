#include <NixieDisplay.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "bluepill.h"
#include "delay.h"
#include "serial2.h"
#include "serial3.h"
#include "Led.h"
#include "Relay.h"
#include "Rtc.h"
#include "stm32f10x_rtc.h"
#include "Pin.h"
#include "stm32f10x_dma.h"
#include "MotionSensor.h"

#define TIME_REFRESH_PERIOD_MS						1000
#define DISPLAY_SHUTDOWN_AFTER_NO_MOVEMENT_MS		900000
#define DISPLAY_BALANCE_MODE_TIME_START_MS			10800000
#define DISPLAY_BALANCE_MODE_TIME_STOP_MS			12600000



Pin		esp8266_pin(GPIOB, GPIO_Pin_1);
MotionSensor motion_sensor;
NixieDisplay nixie_display;
Rtc 	rtc;
Led 	led_builtin(PC13, Bit_RESET);
Relay 	clicker_relay(PB1, Bit_RESET);
uint32_t time = 0;
uint32_t last_movement_detected;
char 	esp8266_rx_frame[100];
char 	gps_fix_status;
char 	temp_str[100];

uint32_t	a = 0;
uint32_t	b = 0;




void my_dma(void);
void init_receive_interrupt(void);

void main() {

	//deinit
	esp8266_pin.digital_write(LOW);
	motion_sensor.turn_off();

	millis_init();

	serial2_init();			//debug serial
	serial2_send("\n\n\n*** nixie_clock - RESET ***\n\n");

	serial3_init();			//esp8266 serial
	init_receive_interrupt();

    led_builtin.turn_off();

    time = millis();
    uint32_t RTC_Counter;

    //delay(3000);
    esp8266_pin.digital_write(HIGH);
    motion_sensor.turn_on();



    my_dma();

    //nixie_display.custom_numbers(4,5,6,7);
    nixie_display.auto_update_from_rtc = true;


    while (1) {

		if ((millis() - time) > TIME_REFRESH_PERIOD_MS) {
			time = millis();
			if (esp8266_rx_frame[0] != 0) {
				serial2_send(esp8266_rx_frame);
				esp8266_rx_frame[0] = 0;
			}

			if (motion_sensor.is_motion_detected() == true) {
				last_movement_detected = millis();
				nixie_display.turn_on();
				nixie_display.auto_update_from_rtc = true;
				nixie_display.balance_mode_active = false;
			} else {
				if ((millis() - last_movement_detected) > DISPLAY_BALANCE_MODE_TIME_STOP_MS) {
					nixie_display.balance_mode_active = false;
					nixie_display.turn_off();
				} else if ((millis() - last_movement_detected) > DISPLAY_BALANCE_MODE_TIME_START_MS) {
					nixie_display.auto_update_from_rtc = false;
					nixie_display.balance_mode_active = true;
					nixie_display.turn_on();
				} else if ((millis() - last_movement_detected) > DISPLAY_SHUTDOWN_AFTER_NO_MOVEMENT_MS) {
					nixie_display.balance_mode_active = false;
					nixie_display.turn_off();
				}
			}

//#define DISPLAY_TURN_TO_BALANCE_MODE_TIME_MS		10000
//#define DISPLAY_SHUTDOWN_AFTER_NO_MOVEMENT_MS		15000


			RTC_Counter = RTC_GetCounter() % 86400;
			sprintf(temp_str, "RTC time --%d:%d:%d--\n", (int) (RTC_Counter / 3600), (int) (RTC_Counter % 3600) / 60, (int) (RTC_Counter % 3600) % 60);
			serial2_send(temp_str);

			a = a + 1;
			sprintf(temp_str, "a: %i, b: %i\n", (int) a, (int) b);
			serial2_send(temp_str);
		}



	}


} //main()


void my_dma(void) {

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Channel1);

	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);



	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) &a;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) &b;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;

	DMA_Init(DMA1_Channel1, &DMA_InitStruct);

	DMA_Cmd(DMA1_Channel1, ENABLE);


}

void init_receive_interrupt(void) {

	NVIC_InitTypeDef NVIC_InitStructure;

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

} //init_receive_interrupt()
