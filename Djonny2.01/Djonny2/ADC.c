

#include "ADC.h"






/********************************************************************
* 	????????????? ???
*********************************************************************/


void Init_ADC(void) // ????????? ???
{
	ADMUX &=~(1 << REFS1); //  ??????? ?????????? ???????
	ADMUX |=(1 << REFS0); //  ??????? ?????????? ???????
	ADMUX &=~(1 << MUX0); //  MUX0 0000 -????? ADC0	
	ADMUX &=~(1 << MUX1); //  MUX1 0000 -????? ADC0	
	ADMUX &=~(1 << MUX2); //  MUX2 0000 -????? ADC0	
	ADMUX &=~(1 << MUX3); //  MUX3 0000 -????? ADC0	
	ADMUX &=~(1 << MUX4); //  MUX3 0000 -????? ADC0
	
	ADCSRA |=(1 << ADEN);  // ?????????? ???
	ADCSRA |=(1 << ADPS2)|(1 << ADPS1)|(1<<ADPS0);// ???????????? ?? 128 (??????? ??? 64kHz)		
	//ADCSRA |=(1 << ADATE);  // ??????????? ????? ?????? ???
	ADCSRA |=(1 << ADIE); // ?????????? ?????????? ?? ???	
	//ADCSRA |=(1 << ADSC);  // ?????? ??????????????
				 
		

}
