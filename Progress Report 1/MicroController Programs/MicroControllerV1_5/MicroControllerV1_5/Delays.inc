;
;Delay Subroutines
;
delay_5ms:
PUSH R26
PUSH R27
	LDI R26, $E8
	LDI R27, $04
timer5:
	NOP
	SBIW X, 1
	BRNE timer5
POP R27
POP R26
	RET

delay_1ms:
	push r24
	LDI R24, $C8
timer4:
	NOP
	NOP
	DEC R24
	BRNE timer4
	pop r24
	RET

delay_2s:
PUSH R26
PUSH R27
PUSH R24
	ldi R26, $80
	ldi R27, $1A
	ldi R24, $06
timer3:
	NOP
	SBIW X, 1
	brne timer3
	dec R24
	brne timer3
POP R24
POP R27
POP R26
	ret

delay_1_52ms:
PUSH R26
PUSH R27
	ldi r26,$30
	ldi r27,$01
timer2:
	NOP
	SBIW X, 1
	brne timer2
POP R27
POP R26
	ret

delay_37us:
push r24
	ldi R24, 9
timer1:
	NOP
	dec R24
	brne timer1
	pop r24
	ret

delay_40ms:
PUSH R26
PUSH R27
	ldi r26,$40
	ldi r27,$1F
timer0:
	NOP
	SBIW X, 1
	brne timer0
POP R27
POP R26
	ret
