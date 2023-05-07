#include <stdint.h>
#include <util/delay.h>
#include "usart.h"

int16_t main()
{
	int8_t imePrezime[64];
	usartInit(9600);

	while (1)
	{
		usartPutString("Unesite svoje ime i prezime:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		usartGetString(imePrezime);
		usartPutString("Zdravo, ");
		usartPutString(imePrezime);
		usartPutString(". :)\r");
	}
}
