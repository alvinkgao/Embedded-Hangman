/*
 * random_word.c
 *
 * Created: 6/12/2019 5:01:52 PM
 *  Author: alvin
 */ 

#include "adc.h"
#include "avr.h"
#include "random_word.h"

const char* word_bank[20] = {"alligator", "banana", "cookie", "potato", "toast",
	"jellyfish", "maple", "story", "economics", "textbook", "fiscal", "patterns",
"theorem", "income", "relation", "case", "nature", "prime", "bumblebee", "iron"} ;

void set_seed(void) {
	ADMUX = 0x40;
	SET_BIT(ADCSRA, 7);
	unsigned short samp = sample();
	unsigned short samp2;
	for(int i = 0; i < 16; i++) {
		samp2 = sample();
		samp = (samp ^ samp2) << 1;
		
	}
	srand(samp);
}


const char* choose_word(void) {
	int i = rand() % 20;
	return word_bank[i];
}