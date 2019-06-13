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
#include "random_word.h"

int end_game = 0;
int lives = 6;
char inp_str[17] = "";
char out_str[17] = "";
char cur_guess = ' ';
const char* letter_guesses = "";


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

void display_word(const char** word, int remaining_guesses) {
	int finished_flag = 1;
	const char* temp_word = *word;
	for (int i = 0; temp_word[i] != '\0'; i++) {
		out_str[i] = '_';
		for (int j = 0; letter_guesses[j] != '\0'; j++) {
			if(letter_guesses[j] == temp_word[i]) {
				out_str[i] = temp_word[i];
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

void restart(const char** word) {
	end_game = 0;
	*word = choose_word();
	lives = 6;
	strcpy(inp_str, "");
	memset(out_str, 0, sizeof(out_str));
	strcpy(out_str, "");
	strcpy(letter_guesses, "");
	strcpy(cur_guess,' ');
	lcd_clr();
}

void submit(const char** word) {
	char temp[2] = {cur_guess, '\0'};
	int flag = 1;
	
	//check if letter has already been guessed before
	for	(int i = 0; letter_guesses[i] != '\0'; i++) {
		if(cur_guess == letter_guesses[i]) {
			return;
		}
	}
	
	//check if letter exists in word
	const char* temp_word = *word;
	for (int i = 0; temp_word[i] != '\0';i++) {
		if(cur_guess == temp_word[i]) {
			flag = 0;
		}
	}
	lives -= flag;
	strcat(letter_guesses, temp);
}




void on_key_press(int key, char* cur_guess, const char** word) {
	switch(key) {
		case 2: 
		case 3:	
		case 5: 
		case 6: 
		case 7: 
		case 9: 
		case 10: 
		case 11: 
		case 14: letter_change(key, cur_guess);
				break;
		case 12: restart(word);
				break;
		case 16: submit(word);
				break;
		default: break;
	}
}



int main(void)
{
	const char* word;
	lcd_init();
	set_seed();
	word = choose_word();
	while(1) {
		int key = get_key();
		on_key_press(key, &cur_guess, &word);
		while(!end_game) {
			lcd_pos(0,0);
			sprintf(inp_str, "%c %s",cur_guess, letter_guesses);
			lcd_puts2(inp_str);
			avr_wait(250);
			lcd_clr();
			int key = get_key();
			display_word(&word, lives);
			on_key_press(key, &cur_guess, &word);
		}
		

	}

}

