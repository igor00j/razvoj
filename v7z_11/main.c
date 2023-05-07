#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"
#include "lucky.h"

int16_t main()
{
	usartInit(9600);
	int32_t n;
	int8_t ostatak[64];

	while (1)
	{
		usartPutString("Unesite broj:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		n = usartParseInt();

		usartPrintInteger(n);
		if (isLucky(n))
		{
			usartPutString(" - srecan broj \r\r");
		}
		else
		{
			usartPutString(" - nije srecan broj \r\r");
		}
	}
}
