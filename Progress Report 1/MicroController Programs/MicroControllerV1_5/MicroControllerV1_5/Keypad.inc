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

;
; Purpose: Subroutine to set the default password
; to '55555' for testing
;
default_pass:
		LDI R16, $35
		LDI R29, HIGH(code_saved)
		LDI R28, LOW(code_saved)
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		RET
;
; Purpose: To load the passweordinto registers to 
; test against attempts
;
load_pass:
		LDI R29, HIGH(code_saved)
		LDI R28, LOW(code_saved)
		LD	R2, Y+
		LD	R3, Y+
		LD	R4, Y+
		LD	R5, Y+
		LD	R6, Y+
		LD	R7, Y+
		RET

;
; Purpose: To display the saved password on the LCD
;
confirm_load:
		LDI R29, HIGH(code_saved)
		LDI R28, LOW(code_saved)
		LDI R25, 6
label0:
		RCALL delay_1ms
		LD	R16, Y+
		STS	LCD_OUT, R16
		DEC R25
		BRNE label0
		RET

		