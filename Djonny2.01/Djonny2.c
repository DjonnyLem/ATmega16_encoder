
#include "Djonny2.h"



#define COUNT_TIMER 79    // �������� �������� ������� ��� ���������� COUNT_TIMER 8 ~ ������ 1mc; COUNT_TIMER 78 ~ ������ 10mc
//#define LED_PORT 	PORTD
//#define LED_DDR 	DDRD 
//#define LED_PIN		PIND
//#define	LED1 		7	
//#define CountTemp	3
//#define  BLINK 30		//�������� �������� ������� ������� ����������. 

char	high_ADC=0, low_ADC=0;	//���������� ��� ������ �������� ���
unsigned int ADC_value, value;
//unsigned int	 	CountLED = BLINK;			// C������ ��������� LED. ������� �� ����������� �������  30*10mc =0,3���

//unsigned int	 	Count = 0;		//������ �������, �������� �������� ����� �������� �� �������
//unsigned int		count1 = CountTemp;	//������ �������, �������������� ������ �������� Count �������� ��� � 1���
//volatile char static	status = 0;
/*
status|=(1<<0);
status&=(~(1<<0));
status&(1<<0);
*/
/*
 struct  flag
{
	_Bool LED	:1;		//���� LED �����. ���� ����������- ������� BLINK �������� �� �������������� ��������
	volatile char FADC  :1;		//���� ���. ���� ����������- ������ � ADC ��������
	
}Flag;*/

uint8_t *pBuf; // ���������� ���������� ��������� �� ����� (����� ��� ����������� ������ �����??)
/********************************************************************
* ���������� ���������� ������� �� ����������
*********************************************************************/
/*
ISR(TIMER0_COMP_vect)		//���������� ���������� ������� �� ����������
	{
	cli();	//��������� ����������
	ADCSRA |=(1 << ADSC); // ��������� ���������� �� ���	 
	asm ("nop");
	sei();					// ��������� ����������
	}

*/

/********************************************************************
* ���������� ���������� �� ���
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
* 	�������� ����
*********************************************************************/

int main(void)
{
	LCDinit();      //������������� LCD
    Init_Port();		//������������� ������
	//Init_TIMER0_COMP(); //������������� ������� �� ����������
	Init_ADC();			//������������� ���
	//LCD_DATA();
	pBuf=BCD_GetPointerBuf();//�������������� ���������� pBuf ��� ������ ������ �� LCD
	//OCR0 = COUNT_TIMER; //������� ������� �������� ��������
    //TCNT0 =0;			//���������� ������
    sei();								// ����� ���������� ����������
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
* 	������������� ������
*********************************************************************/

	
//	LED_DDR |= 1<<LED1; // ��� ����� D �� �����
//	LED_PORT |= 1<<LED1; //������������� � ���� ����� D ������� �������

//	Enc_DDR &= (~(1<<Enc_A) | (1<<Enc_B)); // ��� ����� D �� ����
//	Enc_PORT &= (~(1<<Enc_A) | (1<<Enc_B)); //������������� � ���� ����� D ��������
	
	DDRA = 0b00000000; // ��� ����� A �� ���� ����� ���
	PORTA |=(1<<PA0); //= 0b00000001; //������������� � ���� ����� A ��������
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
