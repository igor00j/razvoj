#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"
#include "ispis.h"

int16_t main()
{
	usartInit(9600);
	float n = 25.04;
	int8_t ostatak[64];

	while (1)
	{
		usartPutString("Unesite neki realan broj:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		usartGetString(ostatak);

		usartPutString("Unet je broj ");
		ispis(n);
		usartPutString("\r");

		usartPutString("Praznjenje ostatka bafera... ");
		usartPutString(ostatak);
		usartPutString("\r\r");
	}
}
