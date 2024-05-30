/*
 * ADC.c
 *
 * Created: 5/28/2024 3:53:53 AM
 *  Author: Administrator
 */ 
#include "avr/io.h"
#include "ADC.h"

void ADC_conf()
{
	// Set the reference voltage to AVcc (5V)
	//ADMUX |= (1 << REFS0);

	// Set the ADC pre-scale to 128 for 16 MHz clock
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Enable the ADC
	ADCSRA |= (1 << ADEN);
}

// Function to read the ADC value
uint16_t ADC_Read(uint16_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);                                    // Select the corresponding channel
	ADCSRA |= (1 << ADSC);                                                        // Start the conversion
	while (ADCSRA & (1 << ADSC));                                                // Wait for the conversion to finish
	return ADC;
}