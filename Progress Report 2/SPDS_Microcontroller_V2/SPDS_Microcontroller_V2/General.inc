; General.inc

; Various routines for misc. uses

; This subroutine generates the Checksum of the main.asm
; file and then displays it on the LCD
Gen_Check:
		LDI R30, LOW(CHKSUM<<1)
		LDI R31, HIGH(CHKSUM<<1)
		MOV R14, R30
		MOV R15, R31
		CLR R30
		CLR R31
		CLR R18
		CLR R19
		CLR R20
		CLR R21
addvalues:
		LPM R16, Z+
		ADD R18, R16
		ADC R19, R21
		ADC R20, R21
		CP  R30, R14
		BRNE addvalues
		CP  R31, R15
		BRNE addvalues
ChkSum_disp:
		MOV R16, R20
		RCALL Gen_hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R16
		RCALL delay_1ms
		STS LCD_OUT, R17
		MOV R16, R19
		RCALL Gen_hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R16
		RCALL delay_1ms
		STS LCD_OUT, R17
		MOV R16, R18
		RCALL Gen_hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R16
		RCALL delay_1ms
		STS LCD_OUT, R17
		RET


; This routine converts the value of R16
; into ASCII text for either transmission
; using USART or display on the LCD
Gen_hex2asc:
		CLR R14
		MOV R15, R16
		LSR R16
		LSR R16
		LSR R16
		LSR R16
asc_chk:
		CPI R16, $0A
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


; This routine pulls a value from the ADC
; and then sends the value through USART
Gen_ADC:
		LDS R16, $7000
		RCALL Gen_hex2asc
		MOV R18, R17
		RCALL Serial_send
		MOV R18, R16
		RCALL Serial_send
		RET