#include <util/delay.h>

int main(void)
{
	_delay_ms(20); //opóźnienie programowe
	TCCR0|=(1<<WGM01); //ustawienie trybu CTC preskalera
	TCCR0|=(1<<CS02)|(1<<CS00); //ust preskalera
	
    
}
