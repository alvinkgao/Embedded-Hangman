/*
 * keypad.c
 *
 * Created: 6/7/2019 12:16:25 PM
 *  Author: alvin
 */ 

#include "avr.h"
#include "keypad.h"

int is_pressed(int r, int c) {
	for(int i = 0; i < 8; i++) {
		SET_BIT(DDRC, i);
		SET_BIT(PORTC, i);
		
		CLR_BIT(DDRC, i);
		CLR_BIT(PORTC, i);
	}
	SET_BIT(DDRC, r);
	CLR_BIT(PORTC, r);
	SET_BIT(PORTC, 4+c);
	
	return !GET_BIT(PINC,4+c);
}

int get_key() {
	int r, c;
	for(r = 0; r < 4; ++r) {
		for(c = 0; c < 4; ++c) {
			if(is_pressed(r,c)) {
				//return r;
				return ((r*4) + c) + 1;
			}
		}
	}
	return 0;
}
