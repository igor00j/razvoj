#include <stdio.h>
#include <avr/io.h>
#include "usart.h"
#include "ispis.h"

void ispis(float d)
{
	int8_t str[64];
	int8_t tmp = 0;
	sprintf(str, "%.2f", d);
	while(str[tmp] != 0)				// Petlja se izvrsava do nailaska na nul-terminator
	{
		usartPutChar(str[tmp]);		// Slanje tekuceg karaktera
		tmp++;					// Azuriranje pokazivaca na tekuci karakter
	}
}

void usartPrintFloat(float value)
{
	int8_t str[64];
	int8_t tmp = 0;
	int32_t iza = 0;
	int32_t ispred = (int32_t) value;


	while (value != 0)
	{
		str[tmp] = (value % 10) + '0';

		value = value / 10;

		tmp++;
	}

	tmp--;

	while (tmp >= 0)			// Petlja se izvrsava do nailaska na nul-terminator
	{
		usartPutChar(str[tmp]);		// Slanje tekuceg karaktera
		tmp--;						// Azuriranje pokazivaca na tekuci karakter
	}
}
