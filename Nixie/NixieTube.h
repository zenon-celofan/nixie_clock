#ifndef NIXIETUBE_H_
#define NIXIETUBE_H_

#include "stm32f10x.h"
#include "bluepill.h"


class NixieTube {

public:

	NixieTube(uint8_t anode_pin, uint8_t bdc_A_pin = PB12, uint8_t bcd_B_pin = PB14, uint8_t bcd_C_pin = PB15, uint8_t bcd_D_pin = PB13);
	void display_digit(uint8_t digit);
	void turn_on(void);
	void turn_off(void);

private:

	GPIO_TypeDef * 	anode_pin_port;
	uint16_t		anode_pin_number;

	GPIO_TypeDef * 	bcd_A_pin_port;
	uint16_t		bcd_A_pin_number;

	GPIO_TypeDef * 	bcd_B_pin_port;
	uint16_t		bcd_B_pin_number;

	GPIO_TypeDef * 	bcd_C_pin_port;
	uint16_t		bcd_C_pin_number;

	GPIO_TypeDef * 	bcd_D_pin_port;
	uint16_t		bcd_D_pin_number;

	void init_pins(void);

};



#endif /* NIXIETUBE_H_ */
