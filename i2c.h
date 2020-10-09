/*
 * i2c.h
 *
 * Created: 22/09/2020 10:25:34 AM
 *  Author: s4588163
 */ 


#ifndef I2C_H_
#define I2C_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>


#endif /* I2C_H_ */

void i2c_init(void);
void i2c_start(void);
void i2c_write(char);
char i2c_read(void);
char single_byte_read(uint8_t,uint8_t);
int16_t two_byte_read(uint8_t slave_address, uint8_t register_address);
void single_byte_write(uint8_t slave_address, uint8_t register_address, uint8_t data);