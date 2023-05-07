#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"
#include "palindrom.h"

int16_t main()
{
	usartInit(9600);
	int8_t str[64];

	while (1)
	{
		usartPutString("Unesite string:\r");
		while (!usartAvailable())
			;
		_delay_ms(100);

		usartGetString(str);

		usartPutString("Rec \"");
		usartPutString(str);
		if(palindrom(str))
			usartPutString("\" jeste palindrom.\r");
		else
			usartPutString("\" nije palindrom.\r");
		usartPutString("Najduzi njen podpalindrom je \"");
		podPalindrom(str);
		usartPutString("\".\r");
	}
}
