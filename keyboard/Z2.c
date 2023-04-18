#define F_CPU 1000000 //definicja częstotliwości mikroprocesora
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile uint8_t licznik=0;
volatile uint8_t nrKolumny=0;

ISR(TIMER0_OVF_vect){
	
	TCNT0=100;	//ustawienie timera
	
	if(licznik%4==0)
		nrKolumny=(nrKolumny+1)%4;
		
	PORTD =~(1<<(nrKolumny+4)); //ustawienie obecnej kolumny
	_delay_ms(3);
	uint8_t wiersze =PIND & 0x0F; // użycie maski do odczytania stanu wierszy
	
	if(wiersze != 0x0F){ //gdy stan wierszy uległ zmianie
				PORTA=nrKolumny+(licznik%4));
	
	}
	++licznik;
}

int main(void)
{
	DDRD = 0xF0; // Ustawienie klawiatury wyjście=kolumny(4-7), wejście=wiersze (0-3)
	
	DDRC = 0xFF; //ustawienie linii C jako wyjście wyświetlacza segmentowego
	DDRA = 0xFF; //ustawienie lini A jako wyjście diód
	PORTC = 0xFF; //ustawienie początkowego stanu diód
	
	
	TCCR0 |=(CS02); //ustawienie prescalera
	TCNT0= 100; //ustawienie timera ok 40ms
	
	
	TIMSK |=(1<<TOIE0); //zezwolenie na przerwania przy przepełnieniu
	
	sei(); //zezwolenie na globalne przerwania
	while (1)
	{
		PORTC=~PORTC;// zmiana stanu portu c
		_delay_ms(500);	//opóżnienie
	}
}
