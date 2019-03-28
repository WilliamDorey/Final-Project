; Serial.inc

; Routines for serial communications

; Configuration Values
.EQU BAUD = 25
.EQU UTCLB = $18
.EQU FRAME = $86

Serial_init:
		; Sets the baud rate
		LDI R16, $00
		OUT UBRRH, R16
		LDI R16, BAUD
		OUT UBRRL, R16
		; Sets the control and status
		LDI R16, UTCLB
		OUT UCSRB, R16
		; Sets the frame properties
		LDI R16, FRAME
		OUT UCSRC, R16
		RET

; Waits for a byte to be received through USART
Serial_get:
		IN R18, UCSRA
		ANDI R18, $80
		BREQ Serial_get
		IN R18, UDR
		RET

; Sends a byte using USART and then waits for a
; confirmation the byte was received
Serial_send:
		OUT UDR, R18
Serial_wait:
		IN R18, UCSRA
		CPI R18, $20
		BREQ Serial_wait
		RET