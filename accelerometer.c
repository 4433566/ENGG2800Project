/*
 * accelerometer.c
 *
 * Created: 18/09/2020 6:18:02 PM
 *  Author: Jordan Lim
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "lcd.h"
#include "i2c.h"

#define BAUD 4800
#define BRC ((F_CPU/16/BAUD)-1)

#define GRAVITY_MIN 230
#define IDLE_MAX 100

#define SLAVE_ADDRESS 0x53

int accel_x;
int accel_y;
int accel_z;

void init_accelerometer(void){
	single_byte_write(SLAVE_ADDRESS,0x2D,0x08);
}

void read_accel_values(void){
	accel_x = two_byte_read(SLAVE_ADDRESS,0x32);
	accel_y = two_byte_read(SLAVE_ADDRESS,0x34);
	accel_z = two_byte_read(SLAVE_ADDRESS,0x36);
}

int is_tapped(void); //return 1 if tap detected, 0 if nothing

void update_mode(void){ //just after read_accel_values
	if (accel_x > GRAVITY_MIN && abs(accel_y) < IDLE_MAX && abs(accel_z) < IDLE_MAX) { //positive x tilt
		setMode(1);
	}
	else if (abs(accel_x) < IDLE_MAX && accel_y > GRAVITY_MIN && abs(accel_z) < IDLE_MAX ) { //positive y tilt
		setMode(2);
	}
	else if (accel_x < -GRAVITY_MIN && abs(accel_y) < IDLE_MAX && abs(accel_z) < IDLE_MAX) { //negative x tilt
		setMode(3);
	}
	else if (abs(accel_x) < IDLE_MAX && accel_y < -1*GRAVITY_MIN && abs(accel_z) < IDLE_MAX) { //negative y tilt
		setMode(4);
	}
}