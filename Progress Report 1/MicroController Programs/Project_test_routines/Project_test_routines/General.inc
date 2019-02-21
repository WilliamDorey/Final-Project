;
; File name: General.inc
; Descripton:	Subroutines that are used in main.asm
;				but don't fall under a specific module
;

;
; Purpose: To convet the hex value in a register to the asscii value
; split across two registers
; Registers Used: R16(Input), R15, R17:R16(Output)     msb:lsb
;
hex2asc:
		CLR R14
		MOV R15, R16
		LSR R16
		LSR R16
		LSR R16
		LSR R16
asc_chk:
		CPI R16, $0A	; Check if the HEX value is a letter
		BRLO number

letter:
		SUBI R16, $09
		LDI R18, $40
		ADD R16, R18
		RJMP asc_done
number:
		LDI R18, $30
		ADD R16, R18
		RJMP asc_done

next_byte:
		MOV R17, R16
		MOV R16, R15
		ANDI R16, $0F
		RJMP asc_chk

asc_done:
		INC R14
		LDI R18, 2
		CP R14, R18
		BRNE next_byte
		RET
