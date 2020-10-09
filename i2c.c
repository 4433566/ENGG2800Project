/*
 * i2c.c
 *
 * Created: 21/09/2020 10:05:03 PM
 *  Author: jorda
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>

#define BAUD 4800
#define BRC ((F_CPU/16/BAUD)-1)

void print_value(int16_t value);

void i2c_init(void) {
	TWBR = 0x22; //bitrate
	TWCR = (1<<TWEN);
	TWSR = 0x00; //prescaler
	//TWCR &= ~(1<<TWIE);

}

void i2c_start(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//UDR0 = TWCR;
	while (!(TWCR & (1<<TWINT)));
}
	

void i2c_write(uint8_t instruction) {
	TWDR = instruction; //move value to i2c register
	TWCR = (1<<TWINT)|(1<<TWEN); // enable i2c and clear interrupt
	while (!(TWCR & (1<<TWINT))); // write successful			`	
}		

char i2c_read() {
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA); // enable i2c and clear interrupt
	//TWCR |= (1<<TWINT);
	while (!(TWCR & (1<<TWINT))); // read successful, data received in TWDR
	//_delay_ms(1);
	return TWDR;
}

char single_byte_read(uint8_t slave_address, uint8_t register_address){
	i2c_start();
	slave_address = (slave_address<<1);
	i2c_write(slave_address);
	i2c_write(register_address);
	i2c_start();
	slave_address++;
	i2c_write(slave_address);
	char x = i2c_read();
	return x;
}
int16_t two_byte_read(uint8_t slave_address, uint8_t register_address){
	i2c_start();
	slave_address = (slave_address<<1);
	i2c_write(slave_address);
	i2c_write(register_address);
	i2c_start();
	slave_address++;
	i2c_write(slave_address);
	/*
	char x = i2c_read();
	i2c_read();
	*/
	uint8_t lowbyte = i2c_read();
	uint8_t highbyte = i2c_read();
	int16_t fullbyte = (highbyte << 8);
	fullbyte |= lowbyte;
	//UDR0 = '0' + fullbyte;
	_delay_ms(1);
	return fullbyte;
}

void single_byte_write(uint8_t slave_address, uint8_t register_address, uint8_t data) {
	i2c_start();
	slave_address = (slave_address<<1);
	i2c_write(slave_address);
	i2c_write(register_address);
	i2c_write(data);

}

void print_value(int16_t value) { //DELETE

	if (value < 0) {
		UDR0 = '-';
		value = -1*value;
		_delay_ms(2);
	}
	
	int ones = value % 10;
	int tens = (value % 100) / 10;
	int hunds = (value % 1000) / 100;

	
	UDR0 = hunds + '0';
		_delay_ms(2);

	UDR0 = tens + '0';
		_delay_ms(2);

	UDR0 = ones + '0';
		_delay_ms(2);

		
}