#include <avr/interrupt.h>
#include <stdlib.h>
#include "ghero.h"

volatile int16_t ms;

void timerOn()
{
	//inicijalizacija tajmera 0:
	TCCR0A = 0x02; //tajmer 0: CTC mod
	TCCR0B = 0x03; //tajmer 0: fclk = fosc/64
	OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
	TIMSK0 = 0x02; //dozvola prekida tajmera 0
	//usled dostizanja vrednosti registra OCR0A
}

ISR(TIMER0_COMPA_vect)
{
	ms++;
}

uint8_t symGen()
{
	uint8_t symbol;

	if (rand() % 2)
		symbol = rand() % ('9' - '0' + 1) + '0';
	else
		symbol = rand() % ('D' - 'A' + 1) + 'A';

	return symbol;
}

void ghDisplay(uint32_t lives, uint32_t points, uint32_t interval, uint32_t counter)
{
	usartPutString("Lives: ");
	usartPrintInteger(lives);
	usartPutString("  |  Points: ");
	usartPrintInteger(points);
	usartPutString("  |  Interval: ");
	usartPrintInteger(interval);
	usartPutString("  |  Counter: ");
	usartPrintInteger(counter);
	usartPutChar('\r');
}

void ghOperation(uint8_t gen_sym, uint8_t button, uint32_t *lives, uint32_t *points, uint32_t *interval, uint32_t *counter)
{
	if (gen_sym == button && ms < 2000)
	{
		*points = *points + 1;

		*counter = *counter + 1;
		if (*counter == 10)
		{
			*counter = 0;
			*interval = *interval - 100;
		}
		ms = 0;
	}
	else
	{
		*lives = *lives - 1;

		ms = 0;
	}
}

void ghResult(uint32_t *lives, uint32_t *points, uint32_t *interval, uint32_t *counter)
{
	usartPutString("------------\r");
	usartPutString(" Points: ");
	usartPrintInteger(*points);
	usartPutChar('\r');
	usartPutString("------------\r");

	*lives = 3;
	*points = 0;
	*interval = 2000;
	*counter = 0;

	ms = 0;
}
