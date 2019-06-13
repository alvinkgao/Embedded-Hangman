/*
 * adc.c
 *
 * Created: 6/12/2019 12:08:15 PM
 *  Author: alvin
 */ 

#include "adc.h"
#include "avr.h"

unsigned short sample(void) {
	SET_BIT(ADCSRA, 6);
	while(GET_BIT(ADCSRA, 6)) {
	}
	return (unsigned short) ADC;
}