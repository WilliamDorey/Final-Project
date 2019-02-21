;
; File name: Keypad.inc
; Descripton: Subroutines to aide in using a keypad
;

;
; Purpose: To translate the input values from a keypad into
; the ASCII values they represent
; Registers used: R16(Input/Output), R15
;
key_map:
		MOV  R15, R16
		SBRS R15, 3
		RJMP key_map_0
		SBRS R15, 2
		RJMP key_map_2

		SBRC R15, 0
		LDI  R16, '0'
		SBRS R15, 0
		LDI  R16, '*'
		SBRC R15, 1
		LDI  R16, '#'
		RJMP keymap_end

key_map_0:
		SBRC R15, 2
		RJMP key_map_1

		INC  R16
		LDI  R17, $40
		ADD  R16, R17
		RJMP keymap_end

key_map_1:
		LDI R17, $40
		ADD R16, R17
		RJMP keymap_end

key_map_2:
		DEC  R16
		LDI  R17, $40
		ADD  R16, R17
keymap_end:
		RET
