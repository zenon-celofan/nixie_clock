#ifndef RTC_H_
#define RTC_H_

#include "stm32f10x.h"


class Rtc {

public:

	int8_t time_zone;

	Rtc(void);
	uint8_t get_hours(void);
	uint8_t get_minutes(void);
	uint8_t get_seconds(void);
	void set_time(uint32_t counter);

private:

	GPIO_TypeDef * 	UTCp1_pin_port = GPIOA;
	uint16_t		UTCp1_pin_number = GPIO_Pin_8;

	GPIO_TypeDef * 	UTCp2_pin_port = GPIOA;
	uint16_t		UTCp2_pin_number = GPIO_Pin_9;

	void init_pins(void);
	void init_rtc(void);

};

#endif /* RTC_H_ */
