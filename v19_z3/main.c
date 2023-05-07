#include <avr/io.h>
#include <stdint.h>
#include "usart.h"
#include "keypad.h"

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5 , 4};

int16_t main ()
{
	uint8_t button_old, button_new;
	usartInit(9600);
	keypadInit(rows, cols);
	uint8_t cond = 1;
	int32_t n1 = 0, n2 = 0;
	uint8_t op;

	while (1)
	{
		button_new = keypadScan();
		if (button_new != 0x00 && button_new != button_old)
		{
			switch (cond)
			{
				case 1:
					if (button_new >= '0' && button_new <= '9')
					{
						usartPutChar(button_new);
						n1 = 10 * n1 + (button_new - '0');
					}
					else if (button_new == 'A' || button_new == 'B' || button_new == 'C' || button_new == 'D')
					{
						usartPutChar(button_new);
						op = button_new;

						cond = 2;
					}
					break;

				case 2:
					if (button_new >= '0' && button_new <= '9')
					{
						usartPutChar(button_new);
						n2 = 10 * n2 + (button_new - '0');
					}
					else if (button_new == '*')
					{
						usartPutChar(button_new);
						usartOperation(n1, n2, op);

						n1 = 0;
						n2 = 0;
						cond = 1;
					}
			}
		}

		button_old = button_new;
	}
}
