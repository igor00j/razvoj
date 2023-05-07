#include <avr/io.h>
#include <stdint.h>
#include "usart.h"
#include "keypad.h"

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	uint8_t button_old, button_new;
	usartInit(9600);
	keypadInit(rows, cols);

	while (1)
	{
		button_new = keypadScan();
		if (button_new != 0x00 && button_new != button_old)
		{
			usartPutChar(button_new);
			usartPutChar('\n');
		}

		button_old = button_new;
	}

	return 0;
}
