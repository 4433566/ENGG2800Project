/*

 * GccApplication1.c

 *

 * Created: 22/09/2020 1:37:45 PM

 * Author : s4433566

 */ 



#include <avr/io.h>

#define F_CPU 8000000UL	// 8MHz

#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

#include <stdint.h>



int alarm_time = 5; 



//Returns the clock period

uint16_t freq_to_period(uint16_t freq){

	return(1000000UL / freq);

}





// int check_alarm_time(void){

// 	if (current_time >= alarm_time){

// 		return 1;			

// 	} else {

// 		return 0;

// 	} 

// }



//Returns width of pulse

uint16_t dutycycle_to_pulse(float dutycycle, uint16_t clockperiod) {

	return (dutycycle*clockperiod)/100;

}



int main(void)

{

	uint16_t freq = 3000; //Hz

	float dutycycle = 50; //%

	uint16_t clockperiod = freq_to_period(freq);

	uint16_t pulsewidth = dutycycle_to_pulse(dutycycle, clockperiod);	

    

	//Pin OC1A is output -- Port B Pin 1 -- Pin 15

	DDRB = 0xFF;

	

	//Set Max count value

	OCR1A = clockperiod -1;

	

	//Set compare value to be 1 less than pulse width

	if(pulsewidth == 0){

		OCR1B = 0;

	} else {

		OCR1B = pulsewidth -1;

	}

	

	// Set up timer 1 

	// This gives fast PWM with reset occurring on OCR1A compare match 

	//Clock to count at 1MHz (clk/8)

	TCCR1A = (1 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (1 << WGM10);

	TCCR1B = (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (0 << CS10); 

	

// 	if (check_alarm_time = 1){

// 		

// 		

// 		

// 		

// 		

// 		

// 	}

    while (1) {

		_delay_ms(100);

		//Update values

		

		

		freq = freq*105UL/100UL;

		if(freq > 5000) {

			freq = 4000;

		}

		

		clockperiod = freq_to_period(freq);

		pulsewidth = dutycycle_to_pulse(dutycycle, clockperiod);

		

		if (pulsewidth > 0) {

			OCR1B = pulsewidth - 1;

		} else {

			OCR1B = 0;

		}

		

		//Set max count value to be one less than clock period

		OCR1A = clockperiod - 1;

    }

	

}
