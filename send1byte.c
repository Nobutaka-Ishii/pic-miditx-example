#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

void send1byte(uint8_t msgByte){

	uint8_t itr;
	uint8_t tmpReg; // for precise calculation of GPIO output timing.
	// start bit
	GPIObits.GP2 = 0;
	__delay_us(29);
	NOP(); // required for precise timing.

	for( itr=0; itr<8; itr++){
		//GPIObits.GP2 = (uint8_t)(msgByte & 0x1);
		tmpReg = (uint8_t)( (msgByte) & 0x1);
		GPIObits.GP2 = tmpReg;
		msgByte >>= 1;
		__delay_us(20);
		NOP(); // required for precise timing.
	}

	NOP();NOP();NOP();NOP(); // required for precise timing.
	// stop bit
	GPIObits.GP2 = 1;
	__delay_us(32);


}




