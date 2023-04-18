
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 1000000UL

ISR(INT0_vect){
	_delay_ms(50);
	if(!(PIND &(1<<PD2))){ //sprawdzenie czy przycisk jest puszczony
		
		TCNT1=57967;	//ust timera
		TCCR1B |=(1<<CS11)|(1<<CS10); //ust czasu prescalera
		PORTA |=(1<<PA0);//włączenie diody led
		
	}
	
	GIFR &= ~(1<<INTF0); //wyłączenie znacznika przerwania przycisku
}
ISR(TIMER1_OVF_vect){
	TCCR1B &= ~(1<<CS11)|(1<<CS10); //zatrzymanie timera poprzez wyzerowanie prescalera
	PORTA &=~(1<<PA0);//włączenie diody led
	TIFR &=~(1<<TOV0); //wyłączenie znacznika przerwania timera
	
}

int main(void)
{
	cli();	//wyłączenie globalnych przerwań
	DDRA |=(1<<PA0); //zdefiniowanie diody D0
	DDRD | (1<<PD2);	//zdefiniowanie przycisku PD2
	PORTD |=(1<<PD2);	//podciągnięcie zasilania przycisku
	DDRC = 0xFF; //zdefiniowanie wyświetlacza
	
	PORTC = 0xFF; //ustawienie stanu początkowego dla portu C
	
	MCUCR|=(1<<ISC01); //ustawienie zbocza malejącego
	GICR |=(1<<INT0);	//konfiguracja przerwania
	
	TIMSK|= (1<<TOIE1);	//zezwolenie na przerwanie przez przepełnienie
	sei();		//włączenie przerwań globalnych
	
    while (1) 
    {
	PORTC =~PORTC;	//Zmiana stanu świecenia diód
	_delay_ms(500);	//opóźnienie programowe
    }
}
