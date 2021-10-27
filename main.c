// Измерение постоянного тока с помощью AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
unsigned char voltage_counter, current_counter;
unsigned int voltage, current;
volatile unsigned long voltage_buffer, current_buffer;
 
// Обработчик прерывания от АЦП
ISR(ADC_vect)
{
if(ADMUX & 0x0F) // Если был выбран канал ADC1
{
voltage_buffer += ADC; // Накапливаем в буфер значения напряжения
ADMUX = (ADMUX & 0xF0) | 0; // Выбираем канал ADC0
voltage_counter++; // Увеличиваем счетчик измерений
}
else
{
current_buffer += ADC; // Накапливаем в буфер значения тока
ADMUX = (ADMUX & 0xF0) | 1; // Выбираем канал ADC1
current_counter++; // Увеличиваем счетчик измерений
}
}
 
// Функции работы с LCD
#define RS PD0
#define EN PD2
 
// Функция передачи команды
void lcd_com(unsigned char p)
{
PORTD &= ~(1 << RS); // RS = 0 (запись команд)
PORTD |= (1 << EN); // EN = 1 (начало записи команды в LCD)
PORTD &= 0x0F; PORTD |= (p & 0xF0); // Старший нибл
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (конец записи команды в LCD)
_delay_us(100);
PORTD |= (1 << EN); // EN = 1 (начало записи команды в LCD)
PORTD &= 0x0F; PORTD |= (p << 4); // Младший нибл
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (конец записи команды в LCD)
_delay_us(100);
}
 
// Функция передачи данных
void lcd_data(unsigned char p)
{
PORTD |= (1 << RS)|(1 << EN); // RS = 1 (запись данных), EN - 1 (начало записи команды в LCD)
PORTD &= 0x0F; PORTD |= (p & 0xF0); // Старший нибл
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (конец записи команды в LCD)
_delay_us(100);
PORTD |= (1 << EN); // EN = 1 (начало записи команды в LCD)
PORTD &= 0x0F; PORTD |= (p << 4); // Младший нибл
_delay_us(100);
PORTD &= ~(1 << EN); // EN = 0 (конец записи команды в LCD)
_delay_us(100);
}
 
// Функция вывода строки на LCD
void lcd_string(unsigned char command, char *string)
{
lcd_com(0x0C); // Включение дисплея, курсор не видим
lcd_com(command); // Адрес знакоместа
// Выводим символы пока не будет конца строки
while(*string != '\0')
{
lcd_data(*string); // Выводим символ
string++; // Следующий символ строки
}
}
 
// Функция инициализации LCD
void lcd_init(void)
{
DDRD = 0xFF;
PORTD = 0x00;
_delay_ms(50); // Ожидание готовности ЖК-модуля
// Конфигурирование четырехразрядного режима
PORTD |= (1 << PD5);
PORTD &= ~(1 << PD4);
// Активизация четырехразрядного режима
PORTD |= (1 << EN);
PORTD &= ~(1 << EN);
_delay_ms(5);
lcd_com(0x28); // Шина 4 бит, LCD - 2 строки
lcd_com(0x08); // Полное выключение дисплея
lcd_com(0x01); // Очистка дисплея
_delay_us(100);
lcd_com(0x06); // Сдвиг курсора вправо
lcd_com(0x0C); // Включение дисплея, курсор не видим
}
 
int main(void)
{
// Настройка АЦП
ADMUX |= (1 << REFS1)|(1 << REFS0); // Внутренний ИОН 2,56V
ADCSRA |=     (1 << ADEN)  // Разрешение АЦП
             |(1 << ADSC)  // Запуск преобразования
             |(1 << ADFR)  // Непрерывный режим работы АЦП
|(1 << ADPS2)|(1 << ADPS1) // Предделитель на 64 (частота АЦП 125kHz)
             |(1 << ADIE); // Разрешение прерывания от АЦП
 
sei(); // Глобально разрешаем прерывания
 
lcd_init(); // Инициализация LCD
 
_delay_ms(25);
lcd_string(0x80 ,"VOLTS  * AMPERES");
lcd_string(0xC0 ,"  .    *  .     ");
 
while(1)
{
// Вычисляем среднее значение напряжения
if(voltage_counter == 250)
{
voltage = ((voltage_buffer*256*11)/1024)/voltage_counter;
voltage_counter = 0; // Обнуляем счетчик измерений
voltage_buffer = 0; // Обнуляем буфер значений напряжения
lcd_com(0xC0);
lcd_data((voltage/1000%10)+'0');
lcd_data((voltage/100%10)+'0');
lcd_com(0xC3);
lcd_data((voltage/10%10)+'0');
}
 
// Вычисляем среднее значение тока
if(current_counter == 250)
{
current = ((current_buffer*256*10)/1024)/current_counter;
current_counter = 0; // Обнуляем счетчик измерений
current_buffer = 0; // Обнуляем буфер значений тока
lcd_com(0xC9);
lcd_data((current/1000%10)+'0');
lcd_com(0xCB);
lcd_data((current/100%10)+'0');
lcd_data((current/10%10)+'0');
}
 
}
}
