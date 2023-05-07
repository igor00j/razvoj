#include <stdio.h>
#include <avr/io.h>
#include "usart.h"
#include "ispis.h"

void ispis(int32_t d)
{
	int8_t str[64];
	int8_t tmp = 0;
	sprintf(str, "%d", d);
	while(str[tmp] != 0)				// Petlja se izvrsava do nailaska na nul-terminator
	{
		usartPutChar(str[tmp]);		// Slanje tekuceg karaktera
		tmp++;					// Azuriranje pokazivaca na tekuci karakter
	}
}


