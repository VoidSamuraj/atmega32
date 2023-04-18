#include <avr/io.h>
#define F_CPU 1000000UL	//ustawienie częstotliwości na 1Mhz

#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect){	//obsługa przerwań

	_delay_ms(50);	//opuźnieniew w celu eliminacji 
	if(!(PIND & (1<<2))){
		PORTA = ~PORTA; //odwrócenie stanu bitów na porcie C
	}// oczekiwanie na  puszczenie przycisku
	
	GIFR |1<<INT0; //czyszczenie flagi przerwania w rejestrze
}

int main(void)
{
	DDRA=0xFF; //ustawienie lini A jako wyjście
	DDRC=0xFF; //ustawienie lini C jako wyjście
	PORTA=0F0; //ustawienie stanu początkowego diód na porcie A
	PORTC=0xFF;//ustawienie stanu początkowego wyświetlacza na porcie C
	
	DDRD &= ~(1<<2);	//ustawienie portu D2 jako wyjście
	PORTD |= (1<<2);	//podciągnięcie zasilania do przycisku
	
	MCUCR |= (1<<ISC01); //ustawienie zbocza malejącego
	GICR |= (1<<INT0);	//konfiguracja przerwańa
	sei();	//włączenie obsługi przerwań
    while (1) //pętla nieskończona
    {	
		_delay_ms(200); //opóźnienie 200 ms
		PORTC = ~PORTC; //odwrócenie stanu bitów na porcie C
    }
}
