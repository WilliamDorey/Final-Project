;
; File name: LCD.inc
; Description: Subroutines used to control the LCD display
;

.EQU LCD_CONTROL = $2000
.EQU LCD_OUT = $2100

;
; Subroutine to init the LCD display for use
;
init_LCD:
	rcall delay_40ms

	ldi R16, $38
	STS LCD_CONTROL, R16	; Function Set
	rcall delay_37us

	STS LCD_CONTROL, R16	; Function Set
	rcall delay_37us

	ldi R16, $0C
	STS LCD_CONTROL, R16	; Turn on the Display
LCD_reset:			; Label used to reset the display when needed
					; without fully reinitializing
	rcall delay_37us

	ldi R16, $01
	STS LCD_CONTROL, R16	; Clear the Display
	rcall delay_1_52ms

	ldi R16, $06
	STS LCD_CONTROL, R16	; Entry mode set
	rcall delay_37us
	ret

;
; Subroutine to output ASCII characters to the
; most recent spot available on the LCD
;
LCD_text:
	rcall delay_1ms
	lpm   R16, Z+      ;get char from memory
	STS	LCD_OUT, R16
	DEC R25     
	brne  LCD_text
	ret