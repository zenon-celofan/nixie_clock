#include <NixieTube.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bluepill.h"


NixieTube::NixieTube(uint8_t anode_pin, uint8_t bcd_A_pin, uint8_t bcd_B_pin, uint8_t bcd_C_pin, uint8_t bcd_D_pin) {

	anode_pin_port = get_pin_port(anode_pin);
	anode_pin_number = get_pin_number(anode_pin);

	bcd_A_pin_port = get_pin_port(bcd_A_pin);
	bcd_A_pin_number = get_pin_number(bcd_A_pin);

	bcd_B_pin_port = get_pin_port(bcd_B_pin);
	bcd_B_pin_number = get_pin_number(bcd_B_pin);

	bcd_C_pin_port = get_pin_port(bcd_C_pin);
	bcd_C_pin_number = get_pin_number(bcd_C_pin);

	bcd_D_pin_port = get_pin_port(bcd_D_pin);
	bcd_D_pin_number = get_pin_number(bcd_D_pin);

	init_pins();


} //NixieTube()


void NixieTube::init_pins() {

    GPIO_InitTypeDef  GPIO_InitStructure;

    //ANODE
	if (anode_pin_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (anode_pin_port == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (anode_pin_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	GPIO_InitStructure.GPIO_Pin = anode_pin_number;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(anode_pin_port, &GPIO_InitStructure);

	GPIO_WriteBit(anode_pin_port, anode_pin_number, Bit_SET);

	//KATHODES (through 74141 decoder)
	for (uint8_t i = 0; i < 4; i++) {
		GPIO_TypeDef * 	temp_pin_port;
		uint16_t		temp_pin_number;

		if (i == 0) {
			temp_pin_port = bcd_A_pin_port;
			temp_pin_number = bcd_A_pin_number;
		} else if (i == 1) {
			temp_pin_port = bcd_B_pin_port;
			temp_pin_number = bcd_B_pin_number;
		} else if (i == 2) {
			temp_pin_port = bcd_C_pin_port;
			temp_pin_number = bcd_C_pin_number;
		} else if (i == 3) {
			temp_pin_port = bcd_D_pin_port;
			temp_pin_number = bcd_D_pin_number;
		}

		if (temp_pin_port == GPIOA) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		} else if (temp_pin_port == GPIOB) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		} else if (temp_pin_port == GPIOC) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		}
		GPIO_InitStructure.GPIO_Pin = temp_pin_number;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(temp_pin_port, &GPIO_InitStructure);

		GPIO_WriteBit(temp_pin_port, temp_pin_number, Bit_RESET);
	}

} //init_pins()


void NixieTube::display_digit(uint8_t digit) {

	if ((digit & 0x00000001) == 0) {
		GPIO_WriteBit(bcd_A_pin_port, bcd_A_pin_number, Bit_RESET);
	} else {
		GPIO_WriteBit(bcd_A_pin_port, bcd_A_pin_number, Bit_SET);
	}

	digit = digit >> 1;

	if ((digit & 0x00000001) == 0) {
		GPIO_WriteBit(bcd_B_pin_port, bcd_B_pin_number, Bit_RESET);
	} else {
		GPIO_WriteBit(bcd_B_pin_port, bcd_B_pin_number, Bit_SET);
	}

	digit = digit >> 1;

	if ((digit & 0x00000001) == 0) {
		GPIO_WriteBit(bcd_C_pin_port, bcd_C_pin_number, Bit_RESET);
	} else {
		GPIO_WriteBit(bcd_C_pin_port, bcd_C_pin_number, Bit_SET);
	}

	digit = digit >> 1;

	if ((digit & 0x00000001) == 0) {
		GPIO_WriteBit(bcd_D_pin_port, bcd_D_pin_number, Bit_RESET);
	} else {
		GPIO_WriteBit(bcd_D_pin_port, bcd_D_pin_number, Bit_SET);
	}

	if (digit < 10) {
		turn_on();
	} else {
		turn_off();
	}

} //display_digit()


void NixieTube::turn_on(void) {
	GPIO_WriteBit(anode_pin_port, anode_pin_number, Bit_RESET);
} //turn_on()


void NixieTube::turn_off(void) {
	GPIO_WriteBit(anode_pin_port, anode_pin_number, Bit_SET);
} //turn_off()
