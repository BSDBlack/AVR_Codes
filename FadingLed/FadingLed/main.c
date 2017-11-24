/*
 * FadingLedRene.c
 *
 * Created: 05.07.2017 23:46:07
 * Author : BSDBlack
 */ 

#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

void dynamic_delay(uint8_t );

int main(void)
{
	DDRB = 0xFE;
	PORTB = 0x00;
	
	uint8_t button = 0;
	uint8_t on = 0;
	uint8_t duty = 2;
	uint8_t offduty = 18;
	uint8_t loopctr_1 = 0;
	uint8_t pressed = 0;
	
    /* Replace with your application code */
    while (1) 
    {
		button = PINB;
		
		if(button & (1 << PINB0))
		{
			_delay_ms(20);
			++pressed;
			if(1 == on)
			{
				on = 0;
			}
			else
			{
				on = 1;
			}
		}
		else
		{
			pressed = 0;
		}
		
		if(1 == on)
		{
			PORTB |= (1 << PINB1);
			dynamic_delay(duty);
			PORTB &= ~(1 << PINB1);
			dynamic_delay(offduty);
			++loopctr_1;
			if(255 == loopctr_1)
			{
				if(duty < 1000)
				{
					duty += 100;
					offduty -= 100;
				}
				else
				{
					duty -= 100;
					offduty += 100;
				}
				loopctr_1 = 0;
			}
		}
		
		if(pressed > 255)
		{
			PORTB |= (1 << PINB1);
			_delay_ms(250);
			PORTB &= ~(1 << PINB1);
			_delay_ms(250);
			PORTB |= (1 << PINB1);
			_delay_ms(250);
			PORTB &= ~(1 << PINB1);
			_delay_ms(250);
			PORTB |= (1 << PINB1);
			_delay_ms(250);
			PORTB &= ~(1 << PINB1);
			
			on = 0;
			pressed = 0;
		}
		
		
    }
}

void dynamic_delay(uint8_t delay)
{
	while(delay--)
	{
		_delay_us(1);
	}
	
}