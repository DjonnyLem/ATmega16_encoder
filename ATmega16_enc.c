

//������ � ���������

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"           //����� ��� LCD �������

//#define F_CPU 8000000UL
//#define  LED1 6
//#define  LED_PORT PORTD
//#define  LED_DDR DDRD
//#define  BLINK 100
//#define  TLCD 10
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
#define  ON_ADC 10 

signed int Enc_count = 0; //������� ��������� ��������
signed int value_ADC = 0;

//#define	FlagLCD 1
//#define	FlagTimer 0
//unsigned char FlagT;
////unsigned char Tmr; 
//unsigned char LCD;
//unsigned int FlagL;
//signed int EncData =0;// ������� ������� ��������
unsigned int	 	count_ADC	= 0;			// ������� ������� ����������� ���
//unsigned int	 	LCD_count	= TLCD;			// ������� ������� ��������� ���������� ������ LED ����������
//unsigned char NewValue;					//����� ��������� ��������
//unsigned char EncValue;					////������� ��������� ��������
uint8_t *pBuf; // ���������� ���������� ��������� �� ����� (����� ��� ����������� ������ �����??)
uint8_t count =9;
		
struct flag 
{
	_Bool Tmr	:1;
	_Bool Lcd	:1;
	
}Flag;


//************************************************
// ���������� ���������� ������� �� ����������
//************************************************
ISR(TIMER0_COMP_vect)
	{
	cli();	
	if (count_ADC == ON_ADC)
	{
	     ADC_DATA();
    }
	else
	{
	    count_ADC++;
	}	
		
	asm("nop");
    
	sei();
	}

//*****************************************************
//��������� �������� ���������� �� ����������� ������
//*****************************************************

/*   ____      ____
	|	 |	  |    | 	
� __|    |____|    |____
  ____      ____      __
 |    |    |    |    |
B|    |____|    |____|
*/
ISR(INT0_vect)
{
	cli();
	// if (bit_is_clear (Enc_PIN, Enc_A))  	//���� ������� �=0
	// {
		// if (bit_is_clear (Enc_PIN, Enc_B)) 	//��� ����, ���� ������� �=0,
		// {
		    // Enc_count++;						// �� ����������� �������
		// }
		// else if (bit_is_set (Enc_PIN, Enc_B)) //��� ����, ���� ������� �=1,
		// {
		// Enc_count--;						// �� ��������� �������
		// }
		
	// }
	// if (bit_is_set (Enc_PIN, Enc_A))  	//���� ������� �=1
	// {
		if (bit_is_clear (Enc_PIN, Enc_B)) 	//��� ����, ���� ������� �=0,
		{
		Enc_count--;
        //asm ("nop");						// �� ��������� �������
		}
		else if (bit_is_set (Enc_PIN, Enc_B)) //��� ����, ���� ������� �=1,
		{
		Enc_count++;
        //asm ("nop");						// �� ����������� �������
		}
		
	// }
	Flag.Lcd = 1;
	sei();
}
//*****************************************************
// ���������� ���������� �� ���
//*****************************************************
ISR(ADC_vect)
    {
	cli();
	asm ("nop");
	sei();

    }
//*****************************************************
int main(void){
	LCDinit();      //������������� LCD
	Init_TIMER0_COMP();
    Init_INT0();	
	Init_Port();
	LCD_DATA();
	Init_ADC();
/*	Init_Enc();*/
	pBuf=BCD_GetPointerBuf();//�������������� ���������� pBuf ��� ������ ������ �� LCD
	OCR0 = COUNT_TIMER;
    TCNT0 =0;
    sei();								// ����� ���������� ����������
	while(1)
	{
		if (Flag.Lcd == 1)
		//if (FlagL == 1)	
		{
			Flag.Lcd = 0;
			LCD_DATA(); //����� ������ �� �������
		}
		asm("nop");
	}
  
}
//==================================================================
// 	��������� - ������������� ���������� CPU
//==================================================================
void Init_TIMER0_COMP(void)
{
	//=========================================================
	//  � � � � � �  �0	 (����������� ������ 10 ms)
	//	����� CTC	WGM01=1, WGM00=0;
	//	(1/8.000.000)*1024=0.000128
	//	0.001 sec/0.000128=7,8 ������ � 1ms - #define COUNT_TIMER 7
	//	
	//=========================================================
//			  7       6       5       4       3      2        1	
//	TCCR0 = FOC00 | WGM00 | COM01 | COM00 | CS02 | CS01 |	CS00

	TCCR0 |=(1<<CS02)|(0<<CS01)|(1<<CS00)|(1<<WGM01)|(0<<WGM00);  	//��������� 101 -1024; 001 -0; 010 -8; 011 -64; 100 -256
																			//(1<<WGM01) | (0<<WGM00) CTC �����


//TIMSK 
	TIMSK |=(0<<TOIE0)|(1<<OCIE0); //; TOIE01- ��������� ���������� �� ������������, 0- ��������� / OCIE0 1- ��������� ���������� �� ����������, 0- ���������
	
    TIFR |= (1<<OCF0)|(0<<TOV0);
	
	
	
}

void Init_INT0(void)
{
//	������� ���������� �� INT0
//��������� ������� ���������� �� INT0
	GICR |= (1<<INT0);
	//����������� ������� ����������  
	MCUCR |= (1<<ISC01)|(1<<ISC00); //�� ����������� ������
/*	ISC01   ISC00
		0		0 	- ������ ������� �� �����,
		0		1 	- ����� ��������� �� �����,
		1		0	- ���������� ����� �� �����,
		1		1	- ���������� ����� �� �����.
	
*/	
}

void Init_Port(void)
{
	
	//=========================================================
	//������������� ������
/*	
	LED_DDR |= 1<<LED1; // ��� ����� D �� �����
	LED_PORT |= 1<<LED1; //������������� � ���� ����� D ������� �������
*/	
	Enc_DDR &= (~(1<<Enc_A) | (1<<Enc_B)); // ��� ����� D �� ����
	Enc_PORT &= (~(1<<Enc_A) | (1<<Enc_B)); //������������� � ���� ����� D ��������
	
	DDRA = 0b00000000; // ��� ����� A �� ����
	PORTA = 0b00000001; //������������� � ���� ����� A ��������
};

void Init_ADC(void) // ��������� ���
{
	ADMUX |= (0 << REFS1)|(1 << REFS0); //  ������� ���������� �������; MUX 0000 -����� ADC0
	ADCSRA |=     (1 << ADEN)  // ���������� ���
	             |(1 << ADSC)  // ������ ��������������
				 |(1 << ADATE)  // ����������� ����� ������ ���
				 |(1 << ADPS2)|(1 << ADPS1) // ������������ �� 64 (������� ��� 125kHz)
             	 |(1 << ADIE); // ���������� ���������� �� ���
				// |(1 << ADLAR); // ������������ �� ������ ����
	
 }


void LCD_DATA (void)
{
		LCDstringXY("Encoder",0,0);
		LCDstringXY("Volt:",0,1);
		
		BCD_5Int(Enc_count);
		LCDstring_of_sramXY(pBuf,8,0);
		
		BCD_5Int(value_ADC);
		LCDstring_of_sramXY(pBuf,8,1);
		
        //asm("nop");
		//LCDstringXY(EncValueValue,5,1);
}


void ADC_DATA(void)
{
	count_ADC = 0;
	value_ADC=ADCL;
	Flag.Lcd == 1;
	asm("nop");
}
