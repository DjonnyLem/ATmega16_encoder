
#include "Djonny2.h"



#define COUNT_TIMER 79    // значение счетчика таймера для прерывания COUNT_TIMER 8 ~ каждые 1mc; COUNT_TIMER 78 ~ каждые 10mc
//#define LED_PORT 	PORTD
//#define LED_DDR 	DDRD 
//#define LED_PIN		PIND
//#define	LED1 		7	
//#define CountTemp	3
//#define  BLINK 30		//значение счетчика периода мигания светодиода. 

char	high_ADC=0, low_ADC=0;	//переменная для записи значения АЦП
unsigned int ADC_value, value;
//unsigned int	 	CountLED = BLINK;			// Cчетчик импульсов LED. Считает по прерываниям таймера  30*10mc =0,3сек

//unsigned int	 	Count = 0;		//просто счетчик, значение которого будем выводить на дисплей
//unsigned int		count1 = CountTemp;	//просто счетчик, обеспечивающий работу счетчика Count примерно раз в 1сек
//volatile char static	status = 0;
/*
status|=(1<<0);
status&=(~(1<<0));
status&(1<<0);
*/
/*
 struct  flag
{
	_Bool LED	:1;		//Флаг LED диода. Флаг установлен- счетчик BLINK досчитал до установленного значения
	volatile char FADC  :1;		//Флаг АЦП. Флаг установлен- данные с ADC записаны
	
}Flag;*/

uint8_t *pBuf; // определяем переменную указатель на буфер (нужно для обображения вывода чисел??)
/********************************************************************
* Обработчик прерывания таймера по совпадению
*********************************************************************/
/*
ISR(TIMER0_COMP_vect)		//Обработчик прерывания таймера по совпадению
	{
	cli();	//запрещаем прерывания
	ADCSRA |=(1 << ADSC); // Разрешаем прерывания от АЦП	 
	asm ("nop");
	sei();					// разрешаем прерывание
	}

*/

/********************************************************************
* Обработчик прерывания от АЦП
*********************************************************************/
/*
ISR(ADC_vect)
    {
	cli();
	low_ADC = ADCL;
	high_ADC = ADCH;
	ADC_value = high_ADC * 256 + low_ADC;
	asm ("nop");
	//Flag.FADC = 1;
	//status|=(1<<0);
	//Flag.FADC = 1;
	//ADCSRA&=~(1 << ADSC);
	sei();

    }
*/
/********************************************************************
* 	Основной цикл
*********************************************************************/

int main(void)
{
	LCDinit();      //Инициализация LCD
    Init_Port();		//Инициализация портов
	//Init_TIMER0_COMP(); //Инициализация таймера по совпадению
	Init_ADC();			//Инициализация АЦП
	//LCD_DATA();
	pBuf=BCD_GetPointerBuf();//иннициализация переменной pBuf для вывода данных на LCD
	//OCR0 = COUNT_TIMER; //Заносим регистр значение счетчика
    //TCNT0 =0;			//Сбрасываем таймер
    sei();								// Общее разрешение прерываний
	while(1)
	{
		asm("nop");
		
		
		if(ADCSRA&(1<<ADIF))
		{
			low_ADC = ADCL;
			high_ADC = ADCH;
			ADC_value = high_ADC*256+low_ADC;		
			
			ADCSRA|=(1<<ADIF);	
			LCD_DATA();
		
		};
	}


};

void Init_Port(void)
{
	

/********************************************************************
* 	ИНИЦИАЛИЗАЦИЯ ПОРТОВ
*********************************************************************/

	
//	LED_DDR |= 1<<LED1; // БИТ ПОРТА D НА ВЫХОД
//	LED_PORT |= 1<<LED1; //УСТАНАВЛИВАЕМ В БИТЕ ПОРТА D ВЫСОКИЙ УРОВЕНЬ

//	Enc_DDR &= (~(1<<Enc_A) | (1<<Enc_B)); // БИТ ПОРТА D НА ВХОД
//	Enc_PORT &= (~(1<<Enc_A) | (1<<Enc_B)); //УСТАНАВЛИВАЕМ В БИТЕ ПОРТА D ПОДТЯЖКУ
	
	DDRA = 0b00000000; // БИТ ПОРТА A НА ВХОД канал АЦП
	PORTA |=(1<<PA0); //= 0b00000001; //УСТАНАВЛИВАЕМ В БИТЕ ПОРТА A ПОДТЯЖКУ
}	
	
void LCD_DATA (ADC_value)
{
	//	pBuf = ADC_value;
    //    value = pBuf;

		//Flag.FADC == 0;
		//LCDclear();
		
		LCDstringXY("Count:",0,0);
		LCDstringXY("Volt:",0,1);
		
		//BCD_3("123");
		//LCDstring_of_sramXY(pBuf,7,0);
		
		BCD_4Int(ADC_value);
		LCDstring_of_sramXY(pBuf,7,1);
		//LCDstring_of_sramXY;
		//Flag.FADC == 0;
	
		//BCD_5Int(value_ADC);
		//LCDstring_of_sramXY(pBuf,8,1);
		
        //asm("nop");
		//LCDstringXY(EncValueValue,5,1);
};
