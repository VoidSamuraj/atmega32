#include <avr/io.h>
#define F_CPU 1000000UL	//ustawienie częstotliwości na 1Mhz

#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect){	//obsługa przerwań PD2

	PORTA |= (1); //włączenie diody A0
	GIFR |1<<INT0; //czyszczenie flagi przerwania w rejestrze
}

ISR(INT1_vect){	//obsługa przerwań PD3

	PORTA &= ~(1); //wyłączenie diody A0
	GIFR |1<<INT1; //czyszczenie flagi przerwania w rejestrze
}

int main(void)
{
	
		DDRC=0xFF; //ustawienie lini C jako wyjście
		PORTC=0xFF;//ustawienie stanu początkowego wyświetlacza na porcie C
		
		DDRA &= ~0x01;//ustawienie A0 jako wyjście
		PORTA &=0b00000001;//ustawienie stanu początkowego diody A0 
		
		
		DDRD &= ~((1<<2)|(1<<3));	//ustawienie portu D2 i D3 jako wyjście
		PORTD |= ((1<<2)|(1<<3));	//podciągnięcie zasilania do przycisków
	
		MCUCR |= (1<<ISC01 | 1<<ISC00); //ustawienie przerwania dla PD2 i PD3
		GICR |= (1<<INT0 | 1<<INT1);	//konfiguracja rejestru kontroli przerwania
		sei();	//włączenie obsługi przerwań
		
      while (1) //pętla nieskończona
      {
	      _delay_ms(200); //opóźnienie 200 ms
	      PORTC = ~PORTC; //odwrócenie stanu bitów na porcie C
      }
}
