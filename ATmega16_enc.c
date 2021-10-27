

//Работа с энкодером

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"           //Хедер для LCD дисплея

//#define F_CPU 8000000UL
//#define  LED1 6
//#define  LED_PORT PORTD
//#define  LED_DDR DDRD
//#define  BLINK 100
//#define  TLCD 10
//#define  COUNT_TIMER 7   //7
//#define	 Enc_A PD0
//#define	 Enc_B PD1
//#define	 Enc_DDR DDRD
//#define	 Enc_PORT PORTD
//#define	 Enc_PIN PIND

#define F_CPU 8000000UL
#define Enc_PORT 	PORTD 	//
#define Enc_DDR 	DDRD	//
#define Enc_PIN 	PIND	//
#define Enc_A		PD2		//
#define Enc_B		PD1		//
#define  COUNT_TIMER 7     //

signed int Enc_count = 0; //счетчик импульсов энкодера


//#define	FlagLCD 1
//#define	FlagTimer 0
//unsigned char FlagT;
////unsigned char Tmr; 
//unsigned char LCD;
//unsigned int FlagL;
//signed int EncData =0;// счетный регистр энкодера
//unsigned int	 	Count	= BLINK;			// регистр счетчик импульсов LED
//unsigned int	 	LCD_count	= TLCD;			// регистр счетчик импульсов обновления данных LED индикатора
//unsigned char NewValue;					//новое состояние энкодера
//unsigned char EncValue;					////текущее состояние энкодера
uint8_t *pBuf; // определяем переменную указатель на буфер (нужно для обображения вывода чисел??)
uint8_t count =9;
		
struct flag 
{
	_Bool Tmr	:1;
	_Bool Lcd	:1;
	
}Flag;


//************************************************
// обработчик прерывания таймера по совпадению
//************************************************
ISR(TIMER0_COMP_vect)
	{
	cli();	
	asm("nop");
	sei();
	}

//*****************************************************
//Обработка внешнего прерывания по восходящему фронту
//*****************************************************

/*   ____      ____
	|	 |	  |    | 	
А __|    |____|    |____
  ____      ____      __
 |    |    |    |    |
B|    |____|    |____|
*/
ISR(INT0_vect)
{
	cli();
	// if (bit_is_clear (Enc_PIN, Enc_A))  	//если энкодер А=0
	// {
		// if (bit_is_clear (Enc_PIN, Enc_B)) 	//при этом, если энкодер В=0,
		// {
		    // Enc_count++;						// то приращиваем счетчик
		// }
		// else if (bit_is_set (Enc_PIN, Enc_B)) //при этом, если энкодер В=1,
		// {
		// Enc_count--;						// то уменьшаем счетчик
		// }
		
	// }
	// if (bit_is_set (Enc_PIN, Enc_A))  	//если энкодер А=1
	// {
		if (bit_is_clear (Enc_PIN, Enc_B)) 	//при этом, если энкодер В=0,
		{
		Enc_count--;
        //asm ("nop");						// то уменьшаем счетчик
		}
		else if (bit_is_set (Enc_PIN, Enc_B)) //при этом, если энкодер В=1,
		{
		Enc_count++;
        //asm ("nop");						// то приращиваем счетчик
		}
		
	// }
	Flag.Lcd = 1;
	sei();
}
//*****************************************************
// Обработчик прерывания от АЦП
//*****************************************************
ISR(ADC_vect)
	cli();
	asm ("nop");
	sei();


//*****************************************************
int main(void){
	LCDinit();      //Инициализация LCD
	Init_TIMER0_COMP();
    Init_INT0();	
	Init_Port();
	LCD_DATA();
	Init_ADC();
/*	Init_Enc();*/
	pBuf=BCD_GetPointerBuf();//иннициализация переменной pBuf для вывода данных на LCD
	sei();								// Общее разрешение прерываний
	while(1)
	{
		if (Flag.Lcd == 1)
		//if (FlagL == 1)	
		{
			Flag.Lcd = 0;
			LCD_DATA(); //вывод данных на дисплей
		}
		asm("nop");
	}
  
}
//==================================================================
// 	ПРОЦЕДУРА - инициализация аппаратуры CPU
//==================================================================
void Init_TIMER0_COMP(void)
{
	//=========================================================
	//  Т А Й М Е Р  Т0	 (Циклический отсчет 10 ms)
	//	Режим CTC	WGM01=1, WGM00=0;
	//	(1/8.000.000)*1024=0.000128
	//	0.001 sec/0.000128=7,8 тактов в 1ms - #define COUNT_TIMER 7
	//	
	//=========================================================
//			  7       6       5       4       3      2        1	
//	TCCR0 = FOC00 | WGM00 | COM01 | COM00 | CS02 | CS01 |	CS00

	TCCR0 |=(1<<CS02)|(0<<CS01)|(1<<CS00)|(1<<WGM01)|(0<<WGM00);  	//ПРЕСКАЛЕР 101 -1024; 001 -0; 010 -8; 011 -64; 100 -256
																			//(1<<WGM01) | (0<<WGM00) CTC РЕЖИМ


//TIMSK 
	TIMSK |=(0<<TOIE0)|(1<<OCIE0); //; TOIE01- РАЗРЕШАЕТ ПРЕРЫВАНИЕ ПО ПЕРЕПОЛНЕНИЮ, 0- ЗАПРЕЩАЕТ / OCIE0 1- РАЗРЕШАЕТ ПРЕРЫВАНИЕ ПО СОВПАДЕНИЮ, 0- ЗАПРЕЩАЕТ
	
    TIFR |= (1<<OCF0)|(0<<TOV0);
	
	OCR0 = COUNT_TIMER;
	
}

void Init_INT0(void)
{
//	Внешнее прерывание на INT0
//разрешаем внешнее прерывание на INT0
	GICR |= (1<<INT0);
	//настраиваем условие прерывания  
	MCUCR |= (1<<ISC01)|(1<<ISC00); //По восходящему фронту
/*	ISC01   ISC00
		0		0 	- Низкий уровень на ножке,
		0		1 	- Любое изменение на ножке,
		1		0	- Нисходящий фронт на ножке,
		1		1	- Восходящий фронт на ножке.
	
*/	
}

void Init_Port(void)
{
	
	//=========================================================
	//ИНИЦИАЛИЗАЦИЯ ПОРТОВ
/*	
	LED_DDR |= 1<<LED1; // БИТ ПОРТА D НА ВЫХОД
	LED_PORT |= 1<<LED1; //УСТАНАВЛИВАЕМ В БИТЕ ПОРТА D ВЫСОКИЙ УРОВЕНЬ
*/	
	Enc_DDR &= (~(1<<Enc_A) | (1<<Enc_B)); // БИТ ПОРТА D НА ВХОД
	Enc_PORT &= (~(1<<Enc_A) | (1<<Enc_B)); //УСТАНАВЛИВАЕМ В БИТЕ ПОРТА D ПОДТЯЖКУ
	
	
};

void Init_ADC(void) // Настройка АЦП
{
	ADMUX |= (1 << REFS1)|(1 << REFS0); // Внутренний ИОН 2,56V
	ADCSRA |=     (1 << ADEN)  // Разрешение АЦП
	             |(1 << ADSC)  // Запуск преобразования
	             |(1 << ADFR)  // Непрерывный режим работы АЦП
				 |(1 << ADPS2)|(1 << ADPS1) // Предделитель на 64 (частота АЦП 125kHz)
             	 |(1 << ADIE); // Разрешение прерывания от АЦП
 }


void LCD_DATA (void)
{
		LCDstringXY("Знач.энкодера",0,0);
		//LCDstringXY("Аня - доченька",0,1);
		
		BCD_5Int(Enc_count);
		LCDstring_of_sramXY(pBuf,5,1);
        //asm("nop");
		//LCDstringXY(EncValueValue,5,1);
}
