#include "Relay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "bluepill.h"


Relay::Relay(uint8_t relay_pin_param, BitAction active_state_param) {
	relay_pin_port = get_pin_port(relay_pin_param);
	relay_pin_number = get_pin_number(relay_pin_param);
	active_state = active_state_param;

	init_pins();

	turn_off();
}  //Relay()



void Relay::init_pins(void) {

	GPIO_InitTypeDef  GPIO_InitStructure;

	if (relay_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (relay_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (relay_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	GPIO_InitStructure.GPIO_Pin = relay_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(relay_pin_port, &GPIO_InitStructure);

} //init_pins()


void Relay::turn_on(void) {

	GPIO_WriteBit(relay_pin_port, relay_pin_number, active_state);

} //turn_on()


void Relay::turn_off(void) {

	GPIO_WriteBit(relay_pin_port, relay_pin_number, (BitAction) !active_state);

} //turn_off()


void Relay::toggle(void) {

	relay_pin_port->ODR ^= relay_pin_number;

} //toggle()


void Relay::set(uint8_t new_state) {

	GPIO_WriteBit(relay_pin_port, relay_pin_number, (BitAction) new_state);

} //set()


void Relay::set(bool new_state) {

	GPIO_WriteBit(relay_pin_port, relay_pin_number, (BitAction) new_state);

} //set()


void Relay::set(BitAction new_state) {

	GPIO_WriteBit(relay_pin_port, relay_pin_number, new_state);

} //set()
