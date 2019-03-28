; Keypad.inc

; Routines that deal with keypad inputs

; This routine translates the signal from
; the keypad controller IC into the value
; that was pressed on the keypad
Key_map:
		MOV  R15, R16
		SBRS R15, 3
		RJMP Key_map0
		SBRS R15, 2
		RJMP Key_map2

		SBRC R15, 0
		LDI  R16, '0'
		SBRS R15, 0
		LDI  R16, '*'
		SBRC R15, 1
		LDI  R16, '#'
		RJMP Key_map_end

Key_map0:
		SBRC R15, 2
		RJMP Key_map1

		INC  R16
		LDI  R17, $40
		ADD  R16, R17
		RJMP Key_map_end

Key_map1:
		LDI R17, $40
		ADD R16, R17
		RJMP Key_map_end

Key_map2:
		DEC  R16
		LDI  R17, $40
		ADD  R16, R17
Key_map_end:
		RET
