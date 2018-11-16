#include "Rtc.h"
#include "stm32f10x.h"
#include "bluepill.h"
#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"

Rtc::Rtc(void) {

	init_pins();
	init_rtc();

} //Rtc()


void Rtc::set_time(uint32_t counter) {
	RTC_SetCounter(counter);
} //set_time()


uint8_t Rtc::get_hours(void) {

	uint8_t hours;
	uint32_t RTC_Counter;

	RTC_Counter = RTC_GetCounter() % 86400;
	hours = RTC_Counter / 3600;

	//time zone correction
	if (GPIO_ReadInputDataBit(UTCp1_pin_port, UTCp1_pin_number) == Bit_RESET) {
		time_zone = 1;
	} else if (GPIO_ReadInputDataBit(UTCp2_pin_port, UTCp2_pin_number) == Bit_RESET) {
		time_zone = 2;
	} else {
		time_zone = 0;
	}

	hours = (hours + time_zone) % 24;

	return hours;
} //get_hours()



uint8_t Rtc::get_minutes(void) {
	uint8_t minutes;
	uint32_t RTC_Counter;

	RTC_Counter = RTC_GetCounter() % 86400;
	minutes = (RTC_Counter % 3600) / 60;

	return minutes;
} //get_minutes()


uint8_t Rtc::get_seconds(void) {
	uint8_t seconds;
	uint32_t RTC_Counter;

	RTC_Counter = RTC_GetCounter() % 86400;
	seconds = (RTC_Counter % 3600);

	return seconds;
} //get_seconds()

void Rtc::init_pins(void) {

    GPIO_InitTypeDef  GPIO_InitStructure;

    //UTC + 1
	if (UTCp1_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (UTCp1_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (UTCp1_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	GPIO_InitStructure.GPIO_Pin = UTCp1_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UTCp1_pin_port, &GPIO_InitStructure);

    //UTC + 2
	if (UTCp2_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (UTCp2_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (UTCp2_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	GPIO_InitStructure.GPIO_Pin = UTCp2_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UTCp2_pin_port, &GPIO_InitStructure);

} //init_pins()

void Rtc::init_rtc(void) {

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);

	if ((RCC->BDCR & RCC_BDCR_RTCEN) != RCC_BDCR_RTCEN)	{
		RCC_BackupResetCmd(ENABLE);
		RCC_BackupResetCmd(DISABLE);

		RCC_LSEConfig(RCC_LSE_ON);
		while ((RCC->BDCR & RCC_BDCR_LSERDY) != RCC_BDCR_LSERDY) {}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

		RTC_SetPrescaler(0x7FFF);

		RCC_RTCCLKCmd(ENABLE);

		RTC_WaitForSynchro();

	}

} //init_rtc()
