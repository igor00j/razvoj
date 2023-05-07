#include <avr/io.h>
#include <stdint.h>
#include "usart.h"
#include "keypad.h"
#include "prost.h"

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	uint8_t button_old, button_new;
	usartInit(9600);
	keypadInit(rows, cols);
	int32_t n = 0;

	while (1)
	{
		button_new = keypadScan();

		if (button_new != 0x00 && button_new != button_old)
		{
			usartPutChar(button_new);

			if (button_new >= '0' && button_new <= '9')
			{
				n = 10 * n + (button_new - '0');
			}
			else if (button_new == '#')
			{
				usartPutChar('\r');

				if (isPrime(n))
					usartPutString("prost, bin:");
				else
					usartPutString("nije prost, bin:");

				usartPrintBinary(n);

				usartPutString(", dec:");
				usartPrintInteger(n);

				usartPutString(", hex:");
				usartPrintHexadecimal(n);

				usartPutString("\r\r");

				n = 0;
			}
		}

		button_old = button_new;
	}
}
