#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"
#include "jelPangram.h"

int16_t main()
{
	usartInit(9600);
	int8_t str[64];

	while (1) {
		usartPutString("Unesite string:\r");
		while (!usartAvailable())
			;
		_delay_ms(100);

		usartGetString(str);

		if (jelPangram(str))
			usartPutString("Uneti string jeste pangram.\r");
		else
			usartPutString("Uneti string nije pangram.\r");
	}
}
