#ifndef LED_H_
#define LED_H_

#include "stm32f10x_gpio.h"
#include "bluepill.h"

#define ACTIVE_LOW		Bit_RESET
#define ACTIVE_HIGH		Bit_SET

class Led {

private:
	GPIO_TypeDef * 	led_pin_port;
	uint16_t		led_pin_number;
	BitAction		active_state;

	void init_pins(void);

public:
	Led(uint8_t led_pin = PC13, BitAction define_active_state = Bit_SET);

	void turn_on(void);
	void turn_off(void);
	void toggle(void);
	void set(uint8_t new_state = 0x01);
	void set(bool new_state = true);
	void set(BitAction new_state = Bit_SET);

};



#endif /* LED_H_ */
