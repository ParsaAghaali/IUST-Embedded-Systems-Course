
#include <avr/io.h>
#define F_CPU 4000000UL
#include <util/delay.h>

void adjustDutyCycle(void){
	static unsigned char temp=0;
	//increase duty cycle
	if ((PINC&0x01)==0)
	{
		_delay_ms(250);
		if(temp<90) temp+=10;
	}
	//Reset duty cycle
	if ((PINC&0x02)==0)
	{
		_delay_ms(250);
		temp=0;
	}
	//decrease duty cycle
	if ((PINC&0x04)==0)
	{
		_delay_ms(250);
		if(temp>0) temp-=10;
	}
	//duty cycle adjust
	OCR0=(0xFF*temp)/100;
}

//Main function
int main(void){
	//PC0...2 as digital inputs
	DDRC=0b11111000;
	//Set PC0...2 high
	PORTC=0b00000111;
	//Clear duty cycle
	OCR0=0x00;
	//Set PBC or OC0 to output -PWM
	DDRB|=(1<<3);
	//Select fast PWM mode, non inverting output
	TCCR0|=(1<<COM01)|(1<<WGM00)|(1<<WGM01);
	//Set prescaler to 1:8
	TCCR0|=(1<<CS01);
	//main program loop
	while(1){
		adjustDutyCycle();
	}
}

