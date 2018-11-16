#ifndef SERIAL3_H_
#define SERIAL3_H_

#include "stm32f10x.h"


void serial3_init(void);
void serial3_send_char(uint8_t);
void serial3_send(const uint8_t *);


#endif /* SERIAL3_H_ */
