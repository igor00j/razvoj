#include <avr/interrupt.h>
#include "key.h"

volatile int16_t ms;
uint8_t tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t sym;
uint8_t key_old = 0x00, key_new = 0x00;
uint8_t target[2] = {0, 0};

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

void keyOperation(uint8_t key, uint8_t *keys, uint8_t keys_l, uint8_t *target)
{
	key_new = key;

	*(target + 1) = *(keys + tmp[key]);

	if (key_new != key_old || (key_new == key_old && ms >= 2000))
	{
		tmp[key] = 0;
		usartPutChar(*(keys + tmp[key]));

		*(target + 1) = *(keys + tmp[key]);
		*target = 0;

		tmp[key]++;
		ms = 0;
	}
	else if (key_new == key_old && tmp[key] == 0 && ms < 2000)
	{
		usartPutChar(8);
		usartPutChar(*(keys + tmp[key]));

		*target = 1;

		tmp[key]++;
		ms = 0;
	}
	else if (key_new == key_old && tmp[key] < keys_l - 1 && ms < 2000)
	{
		usartPutChar(8);
		usartPutChar(*(keys + tmp[key]));

		*target = 1;

		tmp[key]++;
		ms = 0;
	}
	else if (key_new == key_old && (tmp[key] == keys_l - 1) && ms < 2000)
	{
		usartPutChar(8);
		usartPutChar(*(keys + tmp[key]));

		*target = '1';

		tmp[key] = 0;
		ms = 0;
	}

	key_old = key_new;
}
