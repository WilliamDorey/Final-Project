; LCD.inc

; Routines for using the LCD unit

;LCD addresses for contro and output
.EQU LCD_CON = $2000
.EQU LCD_OUT = $2100

LCD_init:
		RCALL delay_40ms

		; Function set
		LDI R16, $38
		STS LCD_CON, R16
		RCALL delay_37us
		STS LCD_CON, R16
		RCALL delay_37us

		; Turn on the display
		LDI R16, $0C
		STS LCD_CON, R16
LCD_rst:
		RCALL delay_37us

		; Clear the display
		LDI R16, $01
		STS LCD_CON, R16
		RCALL delay_1_52ms

		; Setting the entry mode
		LDI R16, $06
		STS LCD_CON, R16
		RCALL delay_37us
		RET



; Prints a message to the LCD from
; a pattern
LCD_print:
		RCALL delay_1ms
		LPM R16, Z+
		STS LCD_OUT, R16
		DEC R25
		BRNE LCD_print
		RCALL delay_1ms
		RET