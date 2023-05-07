#include <avr/io.h>
#include <stdint.h>
#include "input_event.h"
#include "output_event.h"
#include "keypad.h"
#include "usart.h"
#include "timer0.h"
#include "pin.h"

volatile unsigned long ms = 0;
uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int main()
{
	pinInit(PORT_B, 5, OUTPUT);
	timer0InteruptInit();
	usartInit(115200);
	keypadInit(rows, cols);
	
	int8_t c; 
	uint16_t s, m;
	uint32_t t0;
	
	enum state_t {OFF, ON, MINUTES_INPUT, SECONDS_INPUT, RUN};
	enum state_t state = OFF;
	
	ledOff();
	
	while(1)
	{
		switch(state)
		{
			case OFF:
				c = keypadScan();
				
				if (c == 'A')
				{
					ledOn();
					logTran(OFF, ON);
					state = ON;
				}
				else
					state = OFF;
				break;
				
			case ON:
				c = keypadScan();
				
				if (c == 'B')
				{
					ledOff();
					logTran(ON, OFF);
					state = OFF;
				}
				else if (c == 'C')
				{
					ledBlink();
					s = 0;
					logTran(ON, SECONDS_INPUT);
					state = SECONDS_INPUT;
				}
				else if (c == 'D')
				{
					ledBlink();
					m = 0;
					logTran(ON, MINUTES_INPUT);
					state = MINUTES_INPUT;
				}
				else
					state = ON;
				break;
				
			case MINUTES_INPUT:
				c = keypadScan();
				
				if (c <= '0' && c >= '9' && m <= 99)
				{
					ledBlink();
					min(m*10 + c, 99); 
					logTime(m, s);
					state = MINUTES_INPUT;
				}
				else if (c == 'B')
				{
					ledOff();
					logTran(ON, OFF);
					state = OFF;
				}
				else if (c == 'C')
				{
					ledBlink();
					s = 0;
					logTran(ON, SECONDS_INPUT);
					state = SECONDS_INPUT;
				}
				else if (c == '*')
				{
					t0 = ms; //
					ledBlink();
					logTran(MINUTES_INPUT, RUN);
				}	
				else
					state = MINUTES_INPUT;
				break;
				
			case SECONDS_INPUT:
				c = keypadScan();
				
				if (c == 'B')
				{
					ledOff();
					logTran(ON, OFF);
					state = OFF;
				}
				else if (c == 'D')
				{
					ledBlink();
					m = 0;
					logTran(ON, MINUTES_INPUT);
					state = MINUTES_INPUT;
				}
				else if (c <= '0' && c >= '9' && s <= 59)
				{
					ledBlink();
					min(s*10 + c, 59); 
					logTime(m, s);
					state = SECONDS_INPUT_INPUT;
				}
				else if (c == '*')
				{
					t0 = ms; //
					ledBlink();
					logTran(SECONDS_INPUT, RUN);
				}
				else
					state = SECONDS_INPUT;
				break;
			case RUN:
				c = keypadScan();
				
				if (c == 'B')
				{
					ledOff();
					logTran(RUN, OFF);
					state = OFF;
				}
				else if (secPass(t0) && m == 0 && s == 0)
				{
					ledOff();
					logTran(RUN, OFF);
					state = OFF;
				}
				else if (secPass(t0) && s == 0)
				{
					ledBlink();
					m--;
					s = 59;
					logTime(m, s);
					state = RUN;
			    }
				else if (secPass(t0) && s > 0)
				{
					ledBlink();
					m--;
					s--;
					logTime(m, s);
					state = RUN;
				}
				else
					state = RUN;
				break;	
		}
			
	}

	return 0;	
}
