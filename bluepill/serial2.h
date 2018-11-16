#ifndef SERIAL2_H_
#define SERIAL2_H_

#include "stm32f10x.h"


void serial2_init(void);
void serial2_send_char(char);
void serial2_send(const char*);


#endif /* SERIAL2_H_ */
