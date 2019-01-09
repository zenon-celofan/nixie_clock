#ifndef MOTIONSENSOR_H_
#define MOTIONSENSOR_H_

#include "bluepill.h"
#include "stm32f10x_gpio.h"

class MotionSensor {
public:
	MotionSensor(uint8_t feedback_pin = PB7, uint8_t chip_disable_pin = PB6);
	void turn_on(void);
	void turn_off(void);
	bool is_motion_detected(void);

private:

	GPIO_TypeDef * 	feedback_pin_port;
	uint16_t		feedback_pin_number;

	GPIO_TypeDef * 	chip_disable_A_pin_port;
	uint16_t		chip_disable_A_pin_number;

	void init_pins(void);

};

#endif /* MOTIONSENSOR_H_ */
