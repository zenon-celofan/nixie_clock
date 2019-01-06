#ifndef NIXIEDISPLAY_H_
#define NIXIEDISPLAY_H_

#include <NixieTube.h>
#include "stm32f10x.h"
#include "bluepill.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bluepill.h"

#define NUMBER_OF_NIXIE_TUBES			4


class NixieDisplay {

public:

    uint8_t digit[NUMBER_OF_NIXIE_TUBES];
	bool 	turned_on;
	bool 	cut_rtc_leading_zero;
	bool	auto_update_from_rtc;
	bool	balance_mode_active;
	bool 	digit_active_status[NUMBER_OF_NIXIE_TUBES];

	NixieDisplay();
	void turn_on(void);
	void turn_off(void);
	void refresh(void);
	void show_current_time(void);
	//void auto_update_from_rtc(void);
	void custom_numbers(uint8_t d0 = 0, uint8_t d1 = 0, uint8_t d2 = 0, uint8_t d3 = 0);

private:

	NixieTube nixie_tube[NUMBER_OF_NIXIE_TUBES] {{PA4}, {PA5}, {PA6}, {PA7}};

	void init_auto_refresh(void);

};

#endif /* NIXIEDISPLAY_H_ */
