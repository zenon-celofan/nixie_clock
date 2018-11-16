#include "Led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "bluepill.h"

Led::Led(uint8_t led_pin, BitAction define_active_state) {

	led_pin_port = get_pin_port(led_pin);
	led_pin_number = get_pin_number(led_pin);
	active_state = define_active_state;

	init_pins();

	turn_off();

} //Led


void Led::init_pins(void) {

	GPIO_InitTypeDef  GPIO_InitStructure;

	if (led_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (led_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (led_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	GPIO_InitStructure.GPIO_Pin = led_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(led_pin_port, &GPIO_InitStructure);

} //init_pins()


void Led::turn_on(void) {

	GPIO_WriteBit(led_pin_port, led_pin_number, active_state);

} //turn_on()


void Led::turn_off(void) {

	GPIO_WriteBit(led_pin_port, led_pin_number, (BitAction) !active_state);

} //turn_off()


void Led::toggle(void) {

	led_pin_port->ODR ^= led_pin_number;

} //toggle()


void Led::set(uint8_t new_state) {

	GPIO_WriteBit(led_pin_port, led_pin_number, (BitAction) new_state);

} //set()


void Led::set(bool new_state) {

	GPIO_WriteBit(led_pin_port, led_pin_number, (BitAction) new_state);

} //set()


void Led::set(BitAction new_state) {

	GPIO_WriteBit(led_pin_port, led_pin_number, new_state);

} //set()
