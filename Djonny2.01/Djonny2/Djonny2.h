
#ifndef DJONNY2_H_
#define DJONNY2_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "lcd_hd44780.h"


#include "lcd_hd44780.h"
#include "ADC.h"
#include "TIMER.h"
#include "lcd.h"
void LCD_DATA (void);
void Init_Port(void);

#endif /* DJONNY2_H_ */
