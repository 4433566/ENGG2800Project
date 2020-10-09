/*
 * TX RX Real.c
 *
 * Created: 9/09/2020 1:28:40 PM
 * Author : 45881639 - Jordan Lim
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "accelerometer.h"
#include "i2c.h"



#define BAUD 4800
#define BRC ((F_CPU/16/BAUD)-1)

//Global variables
uint32_t Time;
float CurrentTemperature;      
uint32_t CurrentHumidity;
uint32_t CurrentBrightness;
uint8_t BrightnessLevel;

//inside main
void update_sensors(void){ //calls is_tapped(), isTilted(), updateBrightness(),
	read_accel_values();
	
}
void updateTime(void); //reads Time from 

//LCD appearance control
void updateBrightness(void);
void rotateCW(void); //calls modePrevious().
void rotateCCW(void); //calls modeNext().

//LCD content control
void modeNext(void); //DisplayMode++
void modePrevious(void); //DisplayMode--
void updateDataValues(void);



int main(void)
{

	
	//TXRX
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;

	
	//enable TX and RX pins
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);		//set frame format 8 bit, 2 stop bit	UCSR0C = (1<<USBS0)|(3<<UCSZ00);	//sei();
	//init_serial_stdio(BAUD,0); //DELETE
	init_lcd();
	init_accelerometer();
	//UDR0 = '1';
	i2c_init();
	while(1)
    {
		update_sensors();
		update_mode();
		update_screen_content();
		//cli();
    }
}

//Interrupt handler for received computer data
ISR(USART_RX_vect){
	char received;
	received = UDR0;
	UDR0 = received;
}	

