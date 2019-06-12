/*
 * Project5.c
 *
 * Created: 6/7/2019 12:05:44 PM
 * Author : alvin
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "adc.h"
#include "avr.h"
#include "lcd.h"
#include "keypad.h"

int end_game = 0;
int guesses = 6;
char inp_str[17] = "";
char out_str[17] = "";
char cur_guess = ' ';
const char* letter_guesses = "";
const char* word;

const char* word_bank[20] = {"alligator", "banana", "cookie", "potato", "toast",
	"jellyfish", "maple", "story", "economics", "textbook", "fiscal", "patterns",
	"theorem", "income", "relation", "case", "nature", "prime", "bumblebee", "iron"} ;


const char* choose_word(void) {
	ADMUX = 0x40;
	SET_BIT(ADCSRA, 7);
	unsigned short samp = sample();
	unsigned short samp2;
	for(int i = 0; i < 16; i++) {
		samp2 = sample();
		samp = (samp ^ samp2) << 1;
		
	}
	int i = samp % 20;
	return word_bank[i];
}

void end(int win) {
	lcd_clr();
	lcd_pos(1,0);
	if (win) {
		lcd_puts2("you won");
	}
	else {
		lcd_puts2("you lost");
	}
	avr_wait(1000);
	end_game = 1;

}

void display_word(const char* word, int remaining_guesses) {
	int finished_flag = 1;
	for (int i = 0; word[i] != '\0'; i++) {
		out_str[i] = '_';
		for (int j = 0; letter_guesses[j] != '\0'; j++) {
			if(letter_guesses[j] == word[i]) {
				out_str[i] = word[i];
			}
		}
	}
	
	for (int i = 0; out_str[i] != '\0'; i++) {
		if (out_str[i] == '_') {
			finished_flag = 0;
		}
	}
	
	
	lcd_pos(1,0);
	lcd_puts2(out_str);
	lcd_pos(1,15);
	char temp_str[2] = "";
	sprintf(temp_str, "%d", remaining_guesses);
	lcd_puts2(temp_str);
	strcpy(out_str, "");

	if (remaining_guesses == 0) {
		end(0);
	}
	else if (finished_flag && letter_guesses[0] != '\0') {
		end(1);
	}

}

/*void restart() {
	word = choose_word();
	strcpy(inp_str, "");
	strcpy(out_str, "");
	strcpy(letter_guesses, "");
	guesses = 8;
}*/

void submit(void) {
	char temp[2] = {cur_guess, '\0'};
	int flag = 1;
	
	//check if letter has already been guessed before
	for	(int i = 0; letter_guesses[i] != '\0'; i++) {
		if(cur_guess == letter_guesses[i]) {
			return;
		}
	}
	
	//check if letter exists in word
	for (int i = 0; word[i] != '\0';i++) {
		if(cur_guess == word[i]) {
			flag = 0;
		}
	}
	guesses -= flag;
	strcat(letter_guesses, temp);
}


void letter_guess(int key) {
	switch(key) {
		case 2: //A,B,C
				if(cur_guess == 'a') {
					cur_guess = 'b';
				} 
				else if (cur_guess == 'b') {
					cur_guess = 'c';
				}
				else {
					cur_guess = 'a';
				}
				break;
		case 3: //D,E,F
				if(cur_guess == 'd') {
					cur_guess = 'e';
				}
				else if (cur_guess == 'e') {
					cur_guess = 'f';
				}
				else {
					cur_guess = 'd';
				}
				break;
		case 5: //G,H,I
				if(cur_guess == 'g') {
					cur_guess = 'h';
				}
				else if (cur_guess == 'h') {
					cur_guess = 'i';
				}
				else {
					cur_guess = 'g';
				}
				break;
		case 6: //J,K,L
				if(cur_guess == 'j') {
					cur_guess = 'k';
				}
				else if (cur_guess == 'k') {
					cur_guess = 'l';
				}
				else {
					cur_guess = 'j';
				}
				break;
		case 7: //M,N,O
				if(cur_guess == 'm') {
					cur_guess = 'n';
				}
				else if (cur_guess == 'n') {
					cur_guess = 'o';
				}
				else {
					cur_guess = 'm';
				}
				break;
		case 9: //P,R,S
				if(cur_guess == 'p') {
					cur_guess = 'r';
				}
				else if (cur_guess == 'r') {
					cur_guess = 's';
				}
				else {
					cur_guess = 'p';
				}
				break;
		case 10: //T,U,V
				if(cur_guess == 't') {
					cur_guess = 'u';
				}
				else if (cur_guess == 'u') {
					cur_guess = 'v';
				}
				else {
					cur_guess = 't';
				}
				break;
		case 11: //W,X,Y
				if(cur_guess == 'w') {
					cur_guess = 'x';
				}
				else if (cur_guess == 'x') {
					cur_guess = 'y';
				}
				else {
					cur_guess = 'w';
				}
				break;
		case 14: //Z
			cur_guess = 'z';
			break;
		default: break;
	}
}

void on_key_press(int key) {
	switch(key) {
		case 2: 
		case 3:	
		case 5: 
		case 6: 
		case 7: 
		case 9: 
		case 10: 
		case 11: 
		case 14: letter_guess(key);
				break;
		case 12: //restart();
				break;
		case 16: submit();
				break;
		default: break;
	}
}



int main(void)
{
	lcd_init();

	word = choose_word();
	while(1) {
		avr_wait(250);
		lcd_clr();
		int key = get_key();
		display_word(word, guesses);
		on_key_press(key);
		if(end_game){
			break;
		}
		lcd_pos(0,0);
		sprintf(inp_str, "%c %s",cur_guess, letter_guesses);
		lcd_puts2(inp_str);
		

	}

}

