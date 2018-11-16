#ifndef RELAY_H_
#define RELAY_H_

#include "stm32f10x_gpio.h"
#include "bluepill.h"

#define ACTIVE_LOW		Bit_RESET
#define ACTIVE_HIGH		Bit_SET


class Relay {

public:
	Relay(uint8_t led_pin = PB1, BitAction define_active_state = Bit_RESET);
	void turn_on(void);
	void turn_off(void);
	void toggle(void);
	void set(uint8_t new_state = 0x01);
	void set(bool new_state = true);
	void set(BitAction new_state = Bit_SET);

private:
	GPIO_TypeDef * 	relay_pin_port;
	uint16_t		relay_pin_number;
	BitAction		active_state;

	void init_pins(void);
};

#endif /* RELAY_H_ */
