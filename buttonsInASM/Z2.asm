//PA.0-P1, PA.1-P2 
.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			
			cbi DDRA,0; ustawienie kierunku lini portu jako wejście przycisku1
			cbi DDRA,1; ustawienie kierunku lini portu jako wejście przycisku2

			sbi PORTA,0; podciągnięcie zasilania do przycisku1
			sbi PORTA,1; podciągnięcie zasilania do przycisku2


			sbi DDRA,2; ustawienie linii jako wyjścia diód
			sbi DDRA,3
			sbi DDRA,4
			sbi DDRA,5
			sbi DDRA,6
			sbi DDRA,7



			

loop:			; początek pętli głównej
				; instrukcje pętli głównej
	rjmp loop 	; wróć na początek pętli głównej
