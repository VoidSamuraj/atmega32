// PA0-7 = a-dp, PC0-3 = C4-1
#define F_CPU 1000000UL//ustawienie mikroprocesora na 1MHz
#include <avr/io.h>
#include <avr/interrupt.h>


uint8_t znaki[4] = { // tablica z kodami znaków do wyświetlenia
	0b11000000,
	0b10110000,
	0b10100100,
	0b11111000
	};

volatile uint8_t indeksZnaku=0;	// indeks wskazujący na wyświetlany modół oraz wyświetlany znak

ISR(TIMER0_COMP_vect){
	
	PORTC |= 0x0F;//wyłączenie wyświetlania poprzedniej cyfry aby nie pojawiła się w następnym module
	PORTA= znaki[indeksZnaku]; //wybranie kodu cyfry do wyświetlenia 
	PORTC &= ~(indeksZnaku);	//wybranie modułu na którym będzie wyświetlona liczba 
	
	++indeksZnaku;//zwiększenie indeksu 
	if(indeksZnaku>=4)
		indeksZnaku=0;	//po wyświetleniu na wszystkich modułach, zacznij od początku
}

int main(void)
{
	DDRA= 0xFF;//ustawienie lini A jako wyjście
	DDRC=0x0F;//ustawienie bitów 0-3 jako wyjście
	
	TCCR0 |= (1<<CS01) | (1<<CS00); //ustawienie preskalera na 64
	TCCR0 |= (1<<WGM01);// ustawienie trybu CTC timera 0
	
	OCR0= (uint8_t)(F_CPU / 50 / 64) - 1; // Ustawienie wartości dla częstotliwości 50 Hz
	
	TIMSK |=(1<<OCIE0); //włączenie przerwań timera 0
	sei();//włączenie globalnych przerwań 
	
    while (1) {} //program nie robi nic więcej
}
