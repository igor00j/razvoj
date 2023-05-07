#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"
#include "ispis.h"

int16_t main()
{
	usartInit(9600);
	int8_t br = 0;
	int8_t tmp = 0;

	while (1)
	{
		usartPutString("Unesite rec:\r");

		while (!usartAvailable())
		;
		_delay_ms(100);

		while (usartAvailable())
		{
			tmp = usartGetChar();
			if (tmp == 97 ||
			    tmp == 101 ||
				tmp == 105 ||
				tmp == 111 ||
				tmp == 117)
				br++;
		}

		usartPutString("Rec ima ");
		ispis(br);
		usartPutString(" samoglasnika.\r");

		br = 0;
	}
}
