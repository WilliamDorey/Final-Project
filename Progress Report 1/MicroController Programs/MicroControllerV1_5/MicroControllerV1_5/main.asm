;
;File: MicroControllerV1_5.asm
;Author: William Dorey
;
;Description:	
;
; Bus Map:
;	Keypad=	$1XXX
;	LCD=	$2XXX
;	ADC=	$7XXX

; Data Segment
.dseg
.org $0100
code_saved: .byte 6
code_enter: .byte 6

;Code segment
.cseg
.INCLUDE "m8515def.inc"

.EQU BAUD = 25   ; 2400bps
.EQU UCTLB = $18 ; Tx Rx enabled
.EQU FRAME = $86 ; Asynchronous, No Parity, 1 Stop bit, 8 Data bits

reset:	RJMP init
		RJMP isr0
		.ORG $1E
init:
		LDI R16, LOW(RAMEND)	; Initialize Stack Pointer
		OUT SPL, R16
		LDI R16, HIGH(RAMEND)
		OUT SPH, R16

		LDI R16, (1<<INT0)		; Enable INT0
		OUT GICR, R16

		LDI R16, $82			; Initialize Data Buses and Interrupt for falling edge of int0
		OUT MCUCR, R16

		RCALL init_uart			; Initialize Serial Communication
		RCALL init_LCD

		RCALL default_pass
		
		RCALL banner
		RCALL confirm_load
		SEI

IDLE:
		RCALL getch	
fini:
		RJMP IDLE

;
; Purpose: To pull a reading from the ADC 
;
adc_:
		LDS R16, $7000
		RCALL hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R17
		RCALL delay_1ms
		STS LCD_OUT, R16
		LDI R16, $10
		RCALL delay_1_52ms
		STS LCD_CONTROL, R16
		RCALL delay_1_52ms
		STS LCD_CONTROL, R16
		RJMP adc_
		RET

;
; Purpose: Interrupt subroutine to read incoming keypad entries
;
isr0:
		LDS R16, $1000
		RCALL key_map
		STS LCD_OUT, R16
		RCALL attempt_pass
		RETI


; Patterns/Strings
BANNER_MSG:	.db	"ACCESS CODE",$00
; External Files
.include "General.inc"
.include "Delays.inc"
.include "LCD.inc"
.include "Keypad.inc"
.include "Serial.inc"
