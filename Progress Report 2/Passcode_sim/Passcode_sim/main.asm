;
; Passcode_sim.asm
;
; Description:	Just a simulation to test
;				a way of checking a passcode

.dseg
.org $0100
code_saved: .byte 6
code_attempt: .byte 6

;Code segment
.cseg
;.INCLUDE "m8515def.inc"

reset:	RJMP init
		.ORG $20
init:	; Initialize Stack Pointer
		LDI R16, LOW(RAMEND)	
		OUT SPL, R16
		LDI R16, HIGH(RAMEND)
		OUT SPH, R16

main:	; stores a "saved" code to test against
		LDI R18, 6
		LDI R28, LOW(code_saved)
		LDI R29, HIGH(code_saved)
		LDI R17, 1
save_saved:
		ST y+, R17
		INC R17
		DEC R18
		BRNE save_saved

		LDI R28, LOW(code_attempt)
		LDI R29, HIGH(code_attempt)

save_attempt:
		; Stores an "attempt" at the passcode
		LDI R16, $01
		ST y+, R16
		LDI R16, $02
		ST y+, R16
		LDI R16, $03
		ST y+, R16
		LDI R16, $04
		ST y+, R16
		LDI R16, $05
		ST y+, R16
		LDI R16, $06
		ST y+, R16

		LDI R18, 6

		LDI R28, LOW(code_saved)
		LDI R29, HIGH(code_saved)
		LDI R26, LOW(code_attempt)
		LDI R27, HIGH(code_attempt)

check:	; Checks the attempt against the saved code
		LD  R16, Y+
		LD  R17, X+

		CP  R16, R17
		BRNE bad

		DEC R18
		BRNE check

good:	; Passcode was correct
		LDI R31, $FF
		RJMP fini

bad:	; Passcode was incorrect
		CLR R31
		RJMP fini
fini:
		RJMP fini
