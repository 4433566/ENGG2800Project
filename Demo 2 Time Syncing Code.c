/*
 * Time Changing.c
 *
 * Created: 16/09/2020 2:53:27 PM
 * Author : kasey
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>

#define SPI_DDR DDRB
#define CS      PINB0
#define MOSI    PINB3
#define SCK     PINB5

#define BAUD 4800
#define BRC ((F_CPU/16/BAUD)-1)

int second, minute, hour, today, screen_pos;
int new, position;
char received[2];
char counter_timer[9];
int set_time_true; 



void SPI_init()
{
	// set CS, MOSI and SCK to output
	SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);
	
	DDRB |= (1<<PINB2);

	// enable SPI, set as master, and clock to fosc/128
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
	SPCR &= ~(1<<CPHA);
}

void SPI_masterTransmitByte(uint8_t data)
{
	// load data into register
	SPDR = data;

	// Wait for transmission complete
	_delay_ms(5);
}

void instructions(uint8_t data, uint8_t RS){
	if (RS) {
		SPI_masterTransmitByte(0xFA);
		} else {
		SPI_masterTransmitByte(0xF8);
	}
	SPI_masterTransmitByte(data&0xF0);
	SPI_masterTransmitByte((data<<4)&0xF0);
}

void TransferData(uint8_t data1, uint8_t RS){
	if (RS){
		instructions(data1,1);
		} else {
		instructions(data1,0);
	}
}

void write_str(char *word){
	for (int i=0; i<strlen(word)+1; i++) {
		TransferData(word[i],1);
	}
}

void initialise_font_mode(void){
	SPI_init();
	DDRD |= (1<<PIND7);
	PORTD &= ~(1<<PIND7);
	_delay_ms(100);
	PORTD |= (1<<PIND7);
	
	_delay_ms(60);
	PORTB |= (1<<CS);
	TransferData(0x3B,0); //FUNCTION SET
	_delay_ms(1);
	
	TransferData(0x3B,0); //FUNCTION SET
	_delay_ms(1);
	
	TransferData(0x08,0); //DISPLAY ON/OFF
	_delay_ms(1);
	
	TransferData(0x10,0); //Cursor Display Control
	_delay_ms(5);
	
	TransferData(0x0C,0); //Display Control, D=1, display on
	_delay_ms(1);
	
	TransferData(0x01,0); //DISPLAY CLEAR
	_delay_ms(15);
	
	TransferData(0x06,0);//ENTRY MODE SET
	
	_delay_ms(100);
	
	PORTB &= ~(1<<CS);
	_delay_ms(5);
	
}


int main(void)
{
	TCNT1 = 63974;
	
	TCCR1A = 0;
	TCCR1B = (1>>CS12)|(1>>CS10); //(1>>WGM12)
	
	TIMSK1 = (1<<TOIE1);
	
	//TXRX
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;

	//enable TX and RX pins
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);		//set frame format 8 bit, 2 stop bit	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	
	today = 0; 
	second = 0;
	minute = 0;
	hour = 0;
	new = 0;
	position = 0; 
	set_time_true = 0;
	screen_pos = 0;
	
	initialise_font_mode();
	
	sei();

    while (1) 
    {
    }
}

void write_number(int num){
	int hundreds, tens, ones;
	if (num > 99) {
		hundreds = num/100 + 48;
		TransferData(hundreds,1);
		tens = num/10 + 48;
		TransferData(tens,1);
	} else {
		tens = num/10 + 48;
		TransferData(tens,1);	
	}
	ones = num % 10 + 48;
	TransferData(ones,1);
}

void write_digit(int number){
	TransferData(number+48,1);
}

void load_time(char* time_received){
	sscanf(time_received,"%2d%2d%2d",&hour,&minute,&second);
	set_time_true = 1;
	
	PORTB |= (1<<CS);
	_delay_ms(10);
		
	TransferData(0x01,0); //DISPLAY CLEAR
	_delay_ms(15);
		
	TransferData(0x80,0);		
	write_number(hour);
	write_str(":");
	TransferData(0x82,0);
	write_number(minute);
	write_str(":");
	TransferData(0x84,0);
	write_number(second);
	
	_delay_ms(10);
	PORTB &= ~(1<<CS);
		
	today = 0;	
}

void load_tones(char* tones_received){
	int frequency;
	int length;
	int different_frequency[5];
	int different_length[5];
	
	PORTB |= (1<<CS);
	_delay_ms(10);
		
	TransferData(0x01,0); //DISPLAY CLEAR
	_delay_ms(15);
	if (screen_pos == 0){
		TransferData(0x90,0);
		write_digit(tones_received[0]-48);
		write_str(":");
		TransferData(0x91,0);
		write_digit(tones_received[1]-48);
		write_digit(tones_received[2]-48);
		write_digit(tones_received[3]-48);
	} else if (screen_pos == 1){
		TransferData(0x93,0);
		write_digit(tones_received[0]-48);
		write_str(":");
		TransferData(0x94,0);
		write_digit(tones_received[1]-48);
		write_digit(tones_received[2]-48);
		write_digit(tones_received[3]-48);
	} else if (screen_pos == 2){
		TransferData(0x88,0);
		write_digit(tones_received[0]-48);
		write_str(":");
		TransferData(0x89,0);
		write_digit(tones_received[1]-48);
		write_digit(tones_received[2]-48);
		write_digit(tones_received[3]-48);
	} else if (screen_pos == 3) {
		TransferData(0x98,0);
		write_digit(tones_received[0]-48);
		write_str(":");
		TransferData(0x99,0);
		write_digit(tones_received[1]-48);
		write_digit(tones_received[2]-48);
		write_digit(tones_received[3]-48);
	}

	_delay_ms(10);
	PORTB &= ~(1<<CS);
	_delay_ms(10);
		
	sscanf(tones_received,"%d%3d",&frequency,&length);
	
	different_frequency[position] = frequency;
	different_length[position] = length;
	position++;
		/*
	
	sprintf(string,"%d%d",frequency,length);
		
	PORTB |= (1<<CS);
	_delay_ms(10);
		
	TransferData(0x01,0); //DISPLAY CLEAR
	_delay_ms(15);
		
	TransferData(0x90,0);
	write_number(frequency);
	write_str(":");
	TransferData(0x94,0);
	write_number(length);
		
	_delay_ms(10);
	PORTB &= ~(1<<CS);
	*/
	today = 0;
	
	screen_pos++;
	
}

void update_time(void){
	if (new==11) {
		second++;
		if (second >= 60) {
			second = 0;
			minute++;
		}
		if (minute >= 60) {
			minute = 0;
			hour++;
		}
		if (hour >= 24) {
			hour = 0;
			minute = 0;
			second = 0;
		}
		new = 0;
		
		PORTB |= (1<<CS);
		_delay_ms(10);
		TransferData(0x01,0); //DISPLAY CLEAR
		_delay_ms(15);
		
		TransferData(0x80,0);
		_delay_ms(10);
		write_number(hour);
		_delay_ms(10);
		write_str(":");
		_delay_ms(10);
		TransferData(0x82,0);
		_delay_ms(10);
		write_number(minute);
		_delay_ms(10);
		write_str(":");
		_delay_ms(10);
		TransferData(0x84,0);
		_delay_ms(10);
		write_number(second);
		
		_delay_ms(10);
		PORTB &= ~(1<<CS);
	} else {
		new++;
	}
	
}

//Timer set to interrupt every one second
ISR (TIMER1_OVF_vect){
	if (set_time_true){
		update_time();
	}	
}

//Interrupt handler for received computer data
ISR(USART_RX_vect){
	char time_received[7];
	char tones_received[5];
	
	if (set_time_true == 0) {
		time_received[today] = UDR0;
		today++;
		if (today == 6){
			time_received[6] = '\0';
			load_time(time_received);	
		}
	} else {		
		tones_received[today] = UDR0; 
		today++;
		if (today==4){
			tones_received[4] = '\0';
			load_tones(tones_received);
		}
	}
}
