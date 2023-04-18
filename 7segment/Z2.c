#define F_CPU 1000000UL//ustawienie mikroprocesora na 1MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint8_t kodyZnakow[16] PROGMEM = { //tablica z kodami znaków do wyświetlenia i zapisanie ich do pamięci danych
	0b11000000,	//0
	0b11111001,	//1
	0b10100100,	//2
	0b10110000, //3
	0b10011001, //4
	0b10010010, //5
	0b10000010, //6
	0b11111000, //7
	0b10000000, //8
	0b10010000, //9
	0b10001000, //A
	0b10000011, //b
	0b11000110, //C
	0b10100001, //d
	0b10000110, //E
	0b10001110 //F
};

uint8_t znaki[4] = {10,15,11,7}; // tablica ze  znakami do wyświetlenia AFB7

volatile uint8_t indeksZnaku=0;	// indeks wskazujący na wyświetlany modół oraz liczbę

ISR(TIMER0_COMP_vect){
	
	PORTC |= 0x0F;//wyłączenie wyświetlania poprzedniej cyfry aby nie pojawiła się w następnym module
	PORTA= pgm_read_byte(&kodyZnakow[znaki[indeksZnaku]]); //wybranie kodu cyfry do wyświetlenia z pamięci danych 
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
	
	OCR0= (uint8_t)(F_CPU / 50 / 64) - 1;; // Ustawienie wartości dla częstotliwości 50 Hz
	
	TIMSK |=(1<<OCIE0); //włączenie przerwań timera 0
	sei();//włączenie globalnych przerwań
	
	while (1) {} //program nie robi nic więcej
}
