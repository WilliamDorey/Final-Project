;Delays.inc

;Time delays

; The subroutinges each load their required
; loop counts and then jumps to the loop
delay_37us:
		PUSH R27
		PUSH R26
		LDI R26, $06
		LDI R27, $00
		RJMP delay_loop

delay_1ms:
		PUSH R27
		PUSH R26
		LDI R26, $C8
		LDI R27, $00
		RJMP delay_loop

delay_1_52ms:
		PUSH R27
		PUSH R26
		LDI R26, $30
		LDI R27, $01
		RJMP delay_loop

delay_5ms:
		PUSH R27
		PUSH R26
		LDI R26, $6F
		LDI R27, $02
		RJMP delay_loop

delay_40ms:
		PUSH R27
		PUSH R26
		LDI R26, $40
		LDI R27, $1F
		RJMP delay_loop

delay_loop:
		SBIW X, 1
		NOP
		BRNE delay_loop
		POP R26
		POP R27
		RET