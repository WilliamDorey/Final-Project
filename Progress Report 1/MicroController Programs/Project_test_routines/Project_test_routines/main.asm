;
;File: Project_test_routines.asm
;Author: William Dorey
;
;Description:	A compilation of different subroutines
;				used to test the individual modules 
;				connected to the micrcontroller
;
; Bus Map:
;	Keypad=	$1XXX
;	LCD=	$2XXX
;	ADC=	$7XXX

; Data Segment
.dseg
.org $0100
code_saved: .byte 6
code_attempt: .byte 6

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

		LDI R19, $41

banner:
		LDI R25, 14
		LDI R30, LOW(LCD_TEST<<1)
		LDI R31, HIGH(LCD_TEST<<1)
		RCALL LCD_text

		rcall delay_1_52ms
		LDI R16, $C0
		STS LCD_CONTROL, R16

main:
		RCALL adc_
;		RCALL key_
;		RCALL TxRx_
		
fini:
		RJMP fini

;
key_:
		LDI R25, 10
		LDI R30, LOW(KEY_TEST<<1)
		LDI R31, HIGH(KEY_TEST<<1)
		RCALL LCD_text
		SEI
		RET
;
adc_:
		LDI R25, 5
		LDI R30, LOW(ADC_TEST<<1)
		LDI R31, HIGH(ADC_TEST<<1)
		RCALL LCD_text
start_adc:
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
		RJMP start_adc
		RET

;
; Purpose: Interrupt subroutine to read incoming keypad entries
;
isr0:
		LDS R16, $1000
		RCALL key_map
		STS LCD_OUT, R16
		LDI R16, $10
		RCALL delay_1_52ms
		STS LCD_CONTROL, R16
		RETI

LCD_TEST:	.db	"This is a test"
ADC_TEST:	.db	"ADC: ",$00
KEY_TEST:	.db "Last key: " 
TXR_TEST:	.db	"Tx: * Rx: *", $00

; External Files
.include "General.inc"
.include "Delays.inc"
.include "LCD.inc"
.include "Keypad.inc"
.include "Serial.inc"
