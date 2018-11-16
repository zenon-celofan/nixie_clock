#ifndef PIN_H_
#define PIN_H_

#include "stm32f10x_gpio.h"

class Pin {

private:
	GPIO_TypeDef* GPIO;
	uint16_t number;
	GPIOMode_TypeDef mode = GPIO_Mode_Out_PP;
	GPIOSpeed_TypeDef speed = GPIO_Speed_2MHz;
	BitAction state = Bit_RESET;				//Bit_SET / Bit_RESET

	void init_pin(void);


public:
	Pin(GPIO_TypeDef*, uint16_t);
	Pin(GPIO_TypeDef*, uint16_t, GPIOMode_TypeDef);
	Pin(GPIO_TypeDef*, uint16_t, GPIOMode_TypeDef, GPIOSpeed_TypeDef);

	void digital_write(uint8_t);
	uint8_t digital_read(void);
	void digital_toggle(void);
};


#endif /* PIN_H_ */
