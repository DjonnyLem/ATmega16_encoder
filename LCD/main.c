

#include "main.h"


char buffer [30];
//----------------------------------------
int main(void)
{
    port_init(); //Инициализируем порты
    LCD_init();
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
void port_init(void)
{
    LCD_PORT=0x00;
    LCD_DDR=0xFF;
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
