#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd_hd44780.h"


void port_init(void);
void ss(void);





#endif /* MAIN_H_ */
