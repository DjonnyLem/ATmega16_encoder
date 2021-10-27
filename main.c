// ��������� ����������� ���� � ������� AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
unsigned char voltage_counter, current_counter;
unsigned int voltage, current;
volatile unsigned long voltage_buffer, current_buffer;
 
// ���������� ���������� �� ���
ISR(ADC_vect)
{
if(ADMUX & 0x0F) // ���� ��� ������ ����� ADC1
{
voltage_buffer += ADC; // ����������� � ����� �������� ����������
ADMUX = (ADMUX & 0xF0) | 0; // �������� ����� ADC0
voltage_counter++; // ����������� ������� ���������
}
else
{
current_buffer += ADC; // ����������� � ����� �������� ����
ADMUX = (ADMUX & 0xF0) | 1; // �������� ����� ADC1
current_counter++; // ����������� ������� ���������
}
}
 
// ������� ������ � LCD
#define RS PD0
#define EN PD2
 
// ������� �������� �������
void lcd_com(unsigned char p)
{
PORTD &= ~(1 << RS); // RS = 0 (������ ������)
PORTD |= (1 << EN); // EN = 1 (������ ������ ������� � LCD)
PORTD &= 0x0F; PORTD |= (p & 0xF0); // ������� ����
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (����� ������ ������� � LCD)
_delay_us(100);
PORTD |= (1 << EN); // EN = 1 (������ ������ ������� � LCD)
PORTD &= 0x0F; PORTD |= (p << 4); // ������� ����
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (����� ������ ������� � LCD)
_delay_us(100);
}
 
// ������� �������� ������
void lcd_data(unsigned char p)
{
PORTD |= (1 << RS)|(1 << EN); // RS = 1 (������ ������), EN - 1 (������ ������ ������� � LCD)
PORTD &= 0x0F; PORTD |= (p & 0xF0); // ������� ����
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (����� ������ ������� � LCD)
_delay_us(100);
PORTD |= (1 << EN); // EN = 1 (������ ������ ������� � LCD)
PORTD &= 0x0F; PORTD |= (p << 4); // ������� ����
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (����� ������ ������� � LCD)
_delay_us(100);
}
 
// ������� ������ ������ �� LCD
void lcd_string(unsigned char command, char *string)
{
lcd_com(0x0C); // ��������� �������, ������ �� �����
lcd_com(command); // ����� ����������
// ������� ������� ���� �� ����� ����� ������
while(*string != '\0')
{
lcd_data(*string); // ������� ������
string++; // ��������� ������ ������
}
}
 
// ������� ������������� LCD
void lcd_init(void)
{
DDRD = 0xFF;
PORTD = 0x00;
_delay_ms(50); // �������� ���������� ��-������
// ���������������� ����������������� ������
PORTD |= (1 << PD5);
PORTD &= ~(1 << PD4);
// ����������� ����������������� ������
PORTD |= (1 << EN);
PORTD &= ~(1 << EN);
_delay_ms(5);
lcd_com(0x28); // ���� 4 ���, LCD - 2 ������
lcd_com(0x08); // ������ ���������� �������
lcd_com(0x01); // ������� �������
_delay_us(100);
lcd_com(0x06); // ����� ������� ������
lcd_com(0x0C); // ��������� �������, ������ �� �����
}
 
int main(void)
{
// ��������� ���
ADMUX |= (1 << REFS1)|(1 << REFS0); // ���������� ��� 2,56V
ADCSRA |=     (1 << ADEN)  // ���������� ���
             |(1 << ADSC)  // ������ ��������������
             |(1 << ADFR)  // ����������� ����� ������ ���
|(1 << ADPS2)|(1 << ADPS1) // ������������ �� 64 (������� ��� 125kHz)
             |(1 << ADIE); // ���������� ���������� �� ���
 
sei(); // ��������� ��������� ����������
 
lcd_init(); // ������������� LCD
 
_delay_ms(25);
lcd_string(0x80 ,"VOLTS  * AMPERES");
lcd_string(0xC0 ,"  .    *  .     ");
 
while(1)
{
// ��������� ������� �������� ����������
if(voltage_counter == 250)
{
voltage = ((voltage_buffer*256*11)/1024)/voltage_counter;
voltage_counter = 0; // �������� ������� ���������
voltage_buffer = 0; // �������� ����� �������� ����������
lcd_com(0xC0);
lcd_data((voltage/1000%10)+'0');
lcd_data((voltage/100%10)+'0');
lcd_com(0xC3);
lcd_data((voltage/10%10)+'0');
}
 
// ��������� ������� �������� ����
if(current_counter == 250)
{
current = ((current_buffer*256*10)/1024)/current_counter;
current_counter = 0; // �������� ������� ���������
current_buffer = 0; // �������� ����� �������� ����
lcd_com(0xC9);
lcd_data((current/1000%10)+'0');
lcd_com(0xCB);
lcd_data((current/100%10)+'0');
lcd_data((current/10%10)+'0');
}
 
}
}
