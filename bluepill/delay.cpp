#include "delay.h"
#include "bluepill.h"
#include "stm32f10x.h"


void delay(uint16_t milliseconds) {

	uint32_t d = millis();

	while (millis() -d <= milliseconds);

} //delay()

void delay_us(uint16_t microseconds) {
    long ctr = 2 * microseconds;    //2 = 1us
    // each loop iteration takes 3 cycles to execute.
    while (ctr) {
        asm ("");
        --ctr;
    }
}


//ctr = (8000000 / 3) / 2;
