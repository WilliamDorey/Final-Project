;
; File name: Serial.inc
; Descripton:	Subroutine to aide in serial communication
;				with a raspberry pi
;

;
; Purpose: To initialize the serial communication registers
; according to the values chosen by changing the values of 
; BAUD, UCTLB and FRAME at the top of the code.
; Registers Used: R16
;
init_uart:                 
		LDI r16, 0
		OUT UBRRH, r16
		LDI r16, BAUD
		OUT UBRRL, R16		; configures the bit rate
		LDI R16, UCTLB
		OUT	UCSRB, R16		; configures the Tx/Rx channel
		LDI R16, FRAME
		OUT UCSRC, r16		; configures frame elements
		RET

simple_msg:
		LDI R16, 1
		RCALL putch
		RCALL getch
ready:
		MOV R16, R19
		RCALL putch
		RCALL getch
		MOV R16, R19
		RET
;
; Purpose: To transmit messages consisting of many bytes 
; to the Raspberry Pi through a serial connection
; Registers Used: R16, R17(Input), R30(Input), R31(Input)
;
msg_send:
		MOV R16, R17
		RCALL putch
		RCALL getch
rdy:
		LPM R16, Z+
		RCALL putch
		RCALL getch
		DEC R17
		BRNE rdy
		RET

;
; Purpose: To the read a ingle Byte of data from the serial
; connection
; Registers Used: R16(Output)
;
getch:
		IN R18, UCSRA
		ANDI R18, $80
		BREQ getch
		IN R18, UDR
		RET
;
; Purpose to transmit a single byte of data through serial
; and then wait for the the process to complete
; Registers Used: R16(Input)
;
putch:
		OUT UDR, R16
wait0:
		IN R16, UCSRA
		CPI R16, $20
		BREQ wait0
		RET
