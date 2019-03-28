;
; SPDS_Microcontroller_V2.asm
;
; Author : William Dorey
;
; This is the latest version of the firmware that the Secure Parcel Deposit Station

; Data 
.dseg
pass_code:	.byte 6
pass_atmp:	.byte 6

; Code
.cseg
reset:	RJMP init
inter:	RJMP isr0
		.org $1E

; Main initialization sequence
init:
		; Stack pointer to allow for subroutines
		LDI R16, LOW(RAMEND)
		OUT SPL, R16
		LDI R16, HIGH(RAMEND)
		OUT SPH, R16

		; Selecting interupts to enable
		LDI R16, (1<<INT0)
		OUT GICR, R16

		; Bus and Interrupt initialization
		LDI R16, $82
		OUT MCUCR, R16

		; LCD and Serial communications
		RCALL LCD_init
		RCALL Serial_init

		; Display banner and Checksum
		LDI R25, 9
		LDI R26, LOW(BANR)
		LDI R27, HIGH(BANR)
		RCALL LCD_print
		LDI R16, $C0
		STS LCD_CON, R16
		RCALL Gen_Check

		; Enable interupt signals and solenoid control
		LDI R16, $01
		OUT DDRB, R16
		OUT PORTB, R16
		SEI

wait:
		RCALL Serial_get
		CPI R18, 'W'
		BRNE fini
		RCALL Gen_ADC
fini:
		RJMP wait



isr0:
		PUSH R16
		LDS R16, $1000
		RCALL Key_map
		RETI


; Patterns
BANR:	.db	"SPDS V2.0Checksum "

; List of available Subroutines and their respective files
.include	"General.inc"	; Gen_Check,hex2asc,ADC
.include	"Keypad.inc"	; Key_map
.include	"LCD.inc"		; LCD_init,reset,print
.include	"Delays.inc"	; delay_37us,1ms,1_52ms,5ms,40ms
.include	"Serial.inc"	; Serial_init,get,send

; Marker for end of code
CHKSUM:	.db $00,$00