
#ifndef LCD_HD44780_H_
#define LCD_HD44780_H_

#include "Djonny2.h"

#include <util/delay.h>




/*Указываем к какому порту и к каким пинам подключен дисплей*/
#define LCD_PORT	PORTB
#define LCD_DDR		DDRB
#define LCD_PIN		PINB
#define LCD_DB7		7
#define LCD_DB6		6
#define LCD_DB5		5
#define LCD_DB4		4
#define RS		2
#define RW		1
#define E		0


#define E1  LCD_PORT|=(1<<E); // установка линии E в 1
#define E0	LCD_PORT&=~(1<<E); // установка линии E в 0
#define	RS1	LCD_PORT|=(1<<RS); // установка линии RS в 1 (данные)
#define	RS0	LCD_PORT&=~(1<<RS); // установка линии RS в 0 (команда)

/*Пользовательские функции*/
void LCD_init(void);
void sendhalfbyte (unsigned char c);
void sendbyte(unsigned char c, unsigned char mode);
void sendchar(unsigned char c);
void setpos(unsigned char x, unsigned char y);
void clearlcd();
void str_lcd (char str1[]);


#endif /* LCD_HD44780_H_ */
