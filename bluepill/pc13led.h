#include "stm32f10x.h"

#ifndef PC13LED_H_
#define PC13LED_H_

void pc13led_init(void);
void pc13led_on(void);
void pc13led_off(void);
void pc13led_toggle(void);
void pc13led_set(uint8_t state);

#endif /* PC13LED_H_ */
