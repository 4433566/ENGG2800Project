/*
 * lcd.c
 *
 * Created: 18/09/2020 6:44:07 PM
 *  Author: Jordan Lim
 */ 
#include <avr/io.h>

uint8_t DisplayMode = 1; //1 if stopwatch timer, 2 if temp and humid, 3 if battery voltage, 4 if clock with alarm
uint8_t LastMode = 1;

void init_lcd() {
	DDRD = 0b01000000;
	/* Set the output compare value to be 124 */
	OCR0A = 255;
	
	/* Set the timer to clear on compare match (CTC mode)
	 * and to divide the clock by 64. This starts the timer
	 * running.
	 */
	TCCR0A = (1<<WGM01)|(1<<WGM00)|(1<<COM0A1);
	TCCR0B = (1<<CS00);	
}
void setMode(uint8_t newMode) {
	LastMode = DisplayMode;
	DisplayMode = newMode;
}
void computeBrightness(int ambientLight) {
	
}
void sequenceMode1(void) {
	UDR0 = '1';
}
void sequenceMode2(void) {
	UDR0 = '2';
}
void sequenceMode3(void) {
	UDR0 = '3';
}
void sequenceMode4(void) {
	UDR0 = '4';
}
void update_screen_content(void) {
	if (DisplayMode == 1 && DisplayMode != LastMode) {
		sequenceMode1();
	}
	else if (DisplayMode == 2 && DisplayMode != LastMode) {
		sequenceMode2();		
	}
	else if (DisplayMode == 3 && DisplayMode != LastMode) {
		sequenceMode3();
	}
	else if (DisplayMode == 4 && DisplayMode != LastMode) {
		sequenceMode4();
	}
}

