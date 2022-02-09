
#include "Djonny2.h"



#define COUNT_TIMER 79    // �������� �������� ������� ��� ���������� COUNT_TIMER 8 ~ ������ 1mc; COUNT_TIMER 78 ~ ������ 10mc
//#define LED_PORT 	PORTD
//#define LED_DDR 	DDRD 
//#define LED_PIN		PIND
//#define	LED1 		7	
//#define CountTemp	3
//#define  BLINK 30		//�������� �������� ������� ������� ����������. 

char	high_ADC=0, low_ADC=0;	//���������� ��� ������ �������� ���
volatile unsigned int ADC_value, value1;
//volatile unsigned int value = 0;
//unsigned int	 	CountLED = BLINK;			// C������ ��������� LED. ������� �� ����������� �������  30*10mc =0,3���

//unsigned int	 	Count = 0;		//������ �������, �������� �������� ����� �������� �� �������
//unsigned int		count1 = CountTemp;	//������ �������, �������������� ������ �������� Count �������� ��� � 1���
//volatile char static	status = 0;
/*
status|=(1<<0);
status&=(~(1<<0));
status&(1<<0);
*/

 struct  
{
	_Bool LED	:1;		//���� LED �����. ���� ����������- ������� BLINK �������� �� �������������� ��������
	volatile _Bool FADC  :1;		//���� ���. ���� ����������- ������ � ADC ��������
	
}Flag;

uint8_t *pBuf; // ���������� ���������� ��������� �� ����� (����� ��� ����������� ������ �����??)






/********************************************************************
* ���������� ���������� ������� �� ����������
*********************************************************************/

ISR(TIMER0_COMP_vect)		//���������� ���������� ������� �� ����������
	{
	cli();	//��������� ����������
	ADCSRA |=(1 << ADSC); // ��������� ���������� �� ���	 
	//asm ("nop");
	sei();					// ��������� ����������
	}



/********************************************************************
* ���������� ���������� �� ���
*********************************************************************/

ISR(ADC_vect)
    {
	cli();
	low_ADC = ADCL;
	high_ADC = ADCH;
	ADC_value = high_ADC * 256 + low_ADC;
	//asm ("nop");
	Flag.FADC = 1;
	//status|=(1<<0);
	//Flag.FADC = 1;
	//ADCSRA&=~(1 << ADSC);
	sei();

    }

/********************************************************************
* 	�������� ����
*********************************************************************/

int main(void)
{
	LCDinit();      //������������� LCD
    Init_Port();		//������������� ������
	Init_TIMER0_COMP(); //������������� ������� �� ����������
	Init_ADC();			//������������� ���
	//LCD_DATA();
	pBuf=BCD_GetPointerBuf();//�������������� ���������� pBuf ��� ������ ������ �� LCD
	OCR0 = COUNT_TIMER; //������� ������� �������� ��������
    TCNT0 =0;			//���������� ������
    sei();								// ����� ���������� ����������
	while(1)
	{
		asm("nop");
		
		
		if(Flag.FADC == 1)
		{
;	
			LCD_DATA();
			Flag.FADC = 0;
		
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
	
void LCD_DATA (void)
{
		value1=ADC_value*4.680/1023*100;
		//uint8_t c1=BCD_4Int(value1)%100;
		//uint8_t c1
		//uint8_t c1
		//uint8_t c1
		 
		//LCDdataXY(pBuf,13,0);
		//void LCDcursorl(void)
		//void LCDdata(uint8_t)
		//Flag.FADC == 0;
		//LCDclear();
		
	LCDstringXY("Count:",0,0);
	LCDstringXY("Volt:",0,1);
		
		BCD_4Int(value1);
		LCDstring_of_sramXY(pBuf,7,0);
		
	BCD_Uint(value1);
	LCDstring_of_sramXY(pBuf,6,1);

		//LCDstring_of_sramXY;
		//Flag.FADC == 0;
	
		//BCD_5Int(value_ADC);
		//LCDstring_of_sramXY(pBuf,8,1);
		
        //asm("nop");
		//LCDstringXY(EncValueValue,5,1);
};
/*

Build started 9.2.2022 at 17:57:54
avr-gcc -I"C:\PROJECTS\a_C\Djonny2\."  -mmcu=atmega16 -Wall -gdwarf-2 -std=gnu99            -DF_CPU=8000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -MD -MP -MT Djonny2.o -MF dep/Djonny2.o.d  -c  ../Djonny2.c
avr-gcc -mmcu=atmega16 -Wl,-Map=Djonny2.map Djonny2.o TIMER.o ADC.o lcd.o     -o Djonny2.elf
avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature  Djonny2.elf Djonny2.hex
avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex Djonny2.elf Djonny2.eep || exit 0
avr-objdump -h -S Djonny2.elf > Djonny2.lss



*/