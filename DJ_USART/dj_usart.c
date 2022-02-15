#include "dj_usart.h"
//-----------------------------------------------------------
int main(void)
{
	USART_Init (8);//115200
    while(1)
    {
		
 	 	USART_Transmit('O');//Передаем при включении
  		USART_Transmit('k');//сообщение "Ok!", что свидетельствует
  		USART_Transmit('!');//о правильно работе программы
  		USART_Transmit(0x0d);//переход в начало строки
  		USART_Transmit(0x0a);//переход на новую строку
		_delay_ms(500);
    }
}
