#ifndef NIXIEDISPLAY_H_
#define NIXIEDISPLAY_H_

#include <NixieTube.h>
#include "stm32f10x.h"
#include "bluepill.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bluepill.h"

#define NUMBER_OF_NIXIE_TUBES	4
#define RX_FRAME_SIZE					100
#define	RX_FRAME_START_BYTE				'$'
#define	RX_FRAME_END_BYTE				'\r'

class NixieDisplay {

public:

	uint8_t hours;
	uint8_t minutes;
	int8_t  time_zone;

    uint8_t digit[NUMBER_OF_NIXIE_TUBES];
	bool 	digit_active_status[NUMBER_OF_NIXIE_TUBES];

	NixieDisplay();
	void turn_on(void);
	void turn_off(void);
	void refresh(void);
	void update_time(void);
	void custom_numbers(uint8_t d0 = 0, uint8_t d1 = 0, uint8_t d2 = 0, uint8_t d3 = 0);

private:

	bool turned_on;

	NixieTube nixie_tube[NUMBER_OF_NIXIE_TUBES] {{PA4}, {PA5}, {PA6}, {PA7}};
	void init_auto_refresh(void);

};

#endif /* NIXIEDISPLAY_H_ */
