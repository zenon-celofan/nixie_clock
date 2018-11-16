#ifndef NEO6M_H_
#define NEO6M_H_

#include "stm32f10x.h"
#include "bluepill.h"
//#include "stm32f10x_gpio.h"

#define	 DEFAULT_MINUTES_1			0
#define	 DEFAULT_MINUTES_10			0
#define	 DEFAULT_HOURS_1			2
#define	 DEFAULT_HOURS_10			1


class Neo6M {

public:

	uint16_t current_time;

	Neo6M();


private:

	void init_receive_interrupt(void);

};

#endif /* NEO6M_H_ */
