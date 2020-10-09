/*
 * accelerometer.h
 *
 * Created: 20/09/2020 11:23:49 PM
 *  Author: jorda
 */ 


#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "lcd.h"

void read_accel_values(void);
void update_mode(void);
void init_accelerometer(void);


#endif /* ACCELEROMETER_H_ */