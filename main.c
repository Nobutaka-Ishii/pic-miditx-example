// PIC10F222 Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select bit (8 MHz)
#pragma config MCPU = OFF       // Master Clear Pull-up Enable bit (Pull-up disabled)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config CP = OFF         // Code protection bit (Code protection off)
#pragma config MCLRE = OFF      // GP3/MCLR Pin Function Select bit (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "send1byte.h"

void as(void);

void main(void) {
	asm("MOVWF OSCCAL");
	
	/* initial configuration */

	OPTION = 0b10000100;
	TRISGPIO = 0b00000000;
	ADCON0 = 0b00000000;

	/* main loop */
	while(1){
		// NOTE ON
		send1byte(0x90);
		send1byte(0x40);
		send1byte(0x127);
		
		// active sensing
		as();
		as();
		as();
		
		// NOTE OFF
		send1byte(0x80);
		send1byte(0x40);
		send1byte(0x127);
		
		// active sensing
		as();
		as();
		as();
	}
}

void as(void){
		// active sensing
		__delay_ms(280);
		send1byte(0xfe);
}
