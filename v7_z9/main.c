#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"

int16_t main()
{
	usartInit(9600);
	int32_t n;
	int8_t ostatak[64];

	while (1)
	{
		usartPutString("Unesite neki ceo broj:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		n = usartParseInt();
		usartGetString(ostatak);

		usartPutString("Unet je broj ");
		usartPrintInteger(n);
		usartPutString("\r");

		usartPutString("Praznjenje ostatka bafera... ");
		usartPutString(ostatak);
		usartPutString("\r\r");
	}
}
