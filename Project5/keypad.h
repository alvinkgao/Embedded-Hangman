/*
 * keypad.h
 *
 * Created: 6/7/2019 12:12:45 PM
 *  Author: alvin
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

int is_pressed(int r, int c);
int get_key(void);
void letter_change(int key, char* letter);

#endif /* KEYPAD_H_ */