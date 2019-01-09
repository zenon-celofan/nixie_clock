#include "MotionSensor.h"
#include "bluepill.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
//#include "stm32f10x.h"


MotionSensor::MotionSensor(uint8_t feedback_pin, uint8_t chip_disable_pin) {

	feedback_pin_port = get_pin_port(feedback_pin);
	feedback_pin_number = get_pin_number(feedback_pin);

	chip_disable_A_pin_port = get_pin_port(chip_disable_pin);
	chip_disable_A_pin_number = get_pin_number(chip_disable_pin);

}


void MotionSensor::init_pins() {

	if (feedback_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (feedback_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (feedback_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

    GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = feedback_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(feedback_pin_port, &GPIO_InitStructure);


	if (chip_disable_A_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (chip_disable_A_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (chip_disable_A_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

	GPIO_InitStructure.GPIO_Pin = chip_disable_A_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(chip_disable_A_pin_port, &GPIO_InitStructure);

	GPIO_WriteBit(chip_disable_A_pin_port, chip_disable_A_pin_number, Bit_SET);

} //init_pins()


bool MotionSensor::is_motion_detected(void) {
	return (bool) GPIO_ReadInputDataBit(feedback_pin_port, feedback_pin_number);
} //is_motion_detected()


void MotionSensor::turn_on(void) {
	GPIO_WriteBit(chip_disable_A_pin_port, chip_disable_A_pin_number, Bit_RESET);
} //turn_on()


void MotionSensor::turn_off(void) {
	GPIO_WriteBit(chip_disable_A_pin_port, chip_disable_A_pin_number, Bit_SET);
} //turn_off()
