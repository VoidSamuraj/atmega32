//PA.1-P1, PA.0-S4 

.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100

main: 		
		
			cbi DDRA,1; ustawienie kierunku lini portu jako wejście przycisku
			sbi DDRA,0; ustawienie linii jako wyjście diody
			sbi PORTA,1; podciągnięcie zasilania do przycisku

loop:			
			sbic PINA,1; pominięcie następnej komendy gdy przycisk jest nie wciśnięty
			sbi PORTA,0; włączenie diody

			sbis PINA,1;  pominięcie następnej komendy gdy przycisk jest nie wciśnięty
			cbi PORTA,0; wyłączenie diody


	rjmp loop 	; wróć na początek pętli głównej

