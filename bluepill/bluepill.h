#ifndef BLUEPILL_H_
#define BLUEPILL_H_

#include "stm32f10x.h"


#define FALSE				0
#define TRUE				!FALSE
#define LOW					0
#define HIGH				!LOW



enum {
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
	PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
	PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15
};



uint16_t 		index_of(const char *, const char *, uint16_t);
GPIO_TypeDef * 	get_pin_port(uint8_t);
uint16_t 		get_pin_number(uint8_t);
void 			millis_init(void);
uint32_t 		millis(void);
uint8_t			check_parity(uint16_t integer);

#endif /* BLUEPILL_H_ */
