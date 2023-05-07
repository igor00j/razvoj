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
		usartPutString("Unesite brojni izraz:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		n = usartOperation();

		usartPutString("Vrednost izraza je ");
		usartPrintInteger(n);
		usartPutString("\r");

	}
}
