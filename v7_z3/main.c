#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"
#include "capitalise.h"

int16_t main()
{
	usartInit(9600);
	int8_t rec[64];

	while(1)
	{
		usartPutString("Unesite rec:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		usartGetString(rec);

		capitalise(rec);

		usartPutString(rec);
		usartPutString("\r");
	}
}


