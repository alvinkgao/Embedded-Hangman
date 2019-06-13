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

void letter_change(int key, char* letter ) {
	switch(key) {
		case 2: //A,B,C
		if(*letter == 'a') {
			*letter = 'b';
		}
		else if (*letter == 'b') {
			*letter = 'c';
		}
		else {
			*letter = 'a';
		}
		break;
		case 3: //D,E,F
		if(*letter == 'd') {
			*letter = 'e';
		}
		else if (*letter == 'e') {
			*letter = 'f';
		}
		else {
			*letter = 'd';
		}
		break;
		case 5: //G,H,I
		if(*letter == 'g') {
			*letter = 'h';
		}
		else if (*letter == 'h') {
			*letter = 'i';
		}
		else {
			*letter = 'g';
		}
		break;
		case 6: //J,K,L
		if(*letter == 'j') {
			*letter = 'k';
		}
		else if (*letter == 'k') {
			*letter = 'l';
		}
		else {
			*letter = 'j';
		}
		break;
		case 7: //M,N,O
		if(*letter == 'm') {
			*letter = 'n';
		}
		else if (*letter == 'n') {
			*letter = 'o';
		}
		else {
			*letter = 'm';
		}
		break;
		case 9: //P,R,S
		if(*letter == 'p') {
			*letter = 'r';
		}
		else if (*letter == 'r') {
			*letter = 's';
		}
		else {
			*letter = 'p';
		}
		break;
		case 10: //T,U,V
		if(*letter == 't') {
			*letter = 'u';
		}
		else if (*letter == 'u') {
			*letter = 'v';
		}
		else {
			*letter = 't';
		}
		break;
		case 11: //W,X,Y
		if(*letter == 'w') {
			*letter = 'x';
		}
		else if (*letter == 'x') {
			*letter = 'y';
		}
		else {
			*letter = 'w';
		}
		break;
		case 14: //Z
		*letter = 'z';
		break;
		default: break;
	}
}