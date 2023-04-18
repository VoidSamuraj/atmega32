#define F_CPU 1000000 //definicja częstotliwości mikroprocesora
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_OVF_vect){
	
	TCNT0=100;	//ustawienie timera
	uint8_t wiersze =PIND & 0x0F; // użycie maski do odczytania stanu wierszy
	
	if(wiersze != 0x0F){ //gdy stan wierszy uległ zmianie
		
		DDRD |=0x0F; //zmiana wejść i wyjść
		PORTD &= 0xF0; //zera na liniach kolumn w stanie spoczynku
		DDRD &=0x0F; //zmiana wejść i wyjść
		PORTD |= 0xF0; //podciągnięcie zasilania
		_delay_us(3); //opóźnienie 3ms
		
		uint8_t kolumny=PIND & 0xF0;  //odczytanie stanu kolumn z użyciem maski
			
		DDRD|= 0xF0; //przywrócenie kierunków lini
		PORTD &= 0x0F;//zera na liniach kolumn w stanie spoczynku
		DDRD&= 0xF0; //przywrócenie kierunków lini
		PORTD |= 0x0F;//podciągnięcie zasilania
		
		//PORTA = kolumny;
		PORTA=(~kolumny & 0xF0)|(~wiersze & 0x0F); //wyświetlenie stanu diód na lini A
		
	}
	
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
