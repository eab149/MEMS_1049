/*
 * adc_example.c
 *
 * Created: 3/20/2016 3:52:50 PM
 * Author : WClark
 */ 


/* This program is an example C code for A-to-D conversion using the Atmel chip.

An analog voltage is read (e.g. from potentiometer).

The binary value of the high byte (bits 2-9 of the 10-bit converted value) are echoed out PORTD to be displayed on LEDs.

*/

#include <avr/io.h>
//** GLOBAL VARIABLES **
char sensorvalue = 0; // value read from analog sensor (0-1023)

int main(void)
{
// Setup
	DDRB = 0xFF; // Sets all pins of Port B to output.

	// Set up ADC
	DDRC =  0x00;  // define all Port C bits as input
	PRR = 0x00;  // clear Power Reduction ADC bit (0) in PRR register
	ADCSRA = 1<<ADEN | 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;  // 0x87 // 0b10000111 // Set ADC Enable bit (7) in ADCSRA register, and set ADC prescaler to 128 (bits 2-0 of ADCSRA = ADPS2-ADPS0 = 111)
	ADMUX = 0<<REFS1 | 1<<REFS0 | 1<<ADLAR; //0x60; // 0b01100000  // select Analog Reference voltage to be AVcc (bits 7-6 of ADMUX = 01),
						//left justification (bit 5 of ADMUX = ADLAR = 1);
						//and select channel 0 (bits 3-0 of ADMUX = MUX3-MUX0 = 000)
    
	while(1)
    {
    
	// Read analog input
	ADCSRA |= (1<<ADSC); // Start conversion
	while ((ADCSRA & (1<<ADIF)) ==0); // wait for conversion to finish
	
	sensorvalue = ADCH; // Keep high byte of 10-bit result (throw away lowest two bits)
	
	PORTB = sensorvalue; // echo results back out PORTD

    } // end main while
} // end main
