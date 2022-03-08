#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>



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


#define E1  PORTB|=(1<<E); // установка линии E в 1
#define E0	PORTB&=~(1<<E); // установка линии E в 0
#define	RS1	PORTB|=(1<<RS); // установка линии RS в 1 (данные)
#define	RS0	PORTB&=~(1<<RS); // установка линии RS в 0 (команда)

void port_ini(void);
void sendhalfbyte (unsigned char c);
void LCD_ini(void);
void sendbyte(unsigned char c, unsigned char mode);
void sendchar(unsigned char c);
void setpos(unsigned char x, unsigned  y);
void clearlcd();
void str_lcd (char str1[]);
void ss(void);
char buffer [30];
//----------------------------------------
int main(void)
{
    port_ini(); //Инициализируем порты
    LCD_ini();
    clearlcd();
    setpos(0,0);
    sendchar('n');
    sendchar('m');
    setpos(0,1);
    str_lcd ("Hello World! ");
   _delay_ms(3000);
    clearlcd();
     ss();
}
/*
int main(void)
{
char buffer [30];
float abc = 1.234;
int bcd = 123;

port_ini(); //Инициализируем порты
LCD_ini(); //Инициализируем дисплей
setpos(0, 0);
sprintf(buffer,"%.2f Hellp %d", abc, bcd);
str_lcd(buffer);
setpos(0,1);
str_lcd("asdf");
while(1)
{
}
}
*/
//----------------------------------------
void port_ini(void)
{
    LCD_PORT=0x00;
    LCD_DDR=0xFF;
}

//----------------------------------------
void sendhalfbyte (unsigned char c)
{
    c<<=4;
    E1;                     //включаем линию Е
    _delay_us(50);
    LCD_PORT&=0b00001111;   //стираем информацию на входах DB4-DB7, остальное не трогаем
    LCD_PORT|=c;
    E0;                     //выключаем линию Е
    _delay_us(50);
   
}



//----------------------------------------
void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) 
    {
        RS0;
    }
	else 
    {
        RS1;
    }

	unsigned char hc=0;
	hc=c>>4;
    sendhalfbyte(hc); sendhalfbyte(c);
}
//----------------------------------------
void sendchar(unsigned char c)
{
	sendbyte(c,1);
}
//----------------------------------------
void setpos(unsigned char x, unsigned  y)
{
	char adress;
	adress=(0x40*y+x)|0b10000000;
	sendbyte(adress, 0);
}

//----------------------------------------
void clearlcd()
{
	sendbyte(0b00000001, 0);
	_delay_us(1500);
}
//----------------------------------------
void str_lcd (char str1[])
{  
	unsigned char n;
	for(n=0;str1[n]!='\0';n++)
	sendchar(str1[n]);
}
//----------------------------------------

//----------------------------------------
void LCD_ini(void)
{
    _delay_ms(15); //Ждем 15 мс
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); //4бит-режим (DL=0) и 2 линии (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); //включаем изображение на дисплее (D=1), курсоры никакие не включаем (C=0, B=0)
	_delay_ms(1);
	sendbyte(0b00000110, 0); //курсор (хоть он у нас и невидимый) будет двигаться влево
	_delay_ms(1);
}

//----------------------------------------

void ss(void)
{
unsigned char a;
for (a=0; a!=100; a++)
    {
setpos(0, 0);
  sprintf(buffer,"Volt: %02d", a);
str_lcd(buffer);      

        //sendchar (a);
        _delay_ms(1000);
        clearlcd();
    }
}
