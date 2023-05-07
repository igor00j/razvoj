#include <avr/io.h>
#include "usart.h"
#include "keypad.h"
#include "ghero.h"

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	timerOn();
	usartInit(9600);
	keypadInit(rows, cols);

	uint8_t button_old , button_new;

	uint8_t gen_symbol, input_symbol;

	uint8_t cond = 0;

	uint32_t lives = 3;
	uint32_t points = 0;
	uint32_t time = 2000;
	uint32_t counter = 0;

	while (1)
	{
		if (!cond)
		{
			ghDisplay(lives, points, time, counter);

			gen_symbol = symGen();

			usartPutChar(gen_symbol);
			usartPutString("     ");

			cond = 1;
		}

		button_new = keypadScan();

		if (button_new != 0x00 && button_new != button_old)
		{
			usartPutChar(button_new);
			usartPutChar('\r');

			ghOperation(gen_symbol, button_new, &lives, &points, &time, &counter);

			if (lives == 0)
				ghResult(&lives, &points, &time, &counter);

			cond = 0;
		}

		button_old = button_new;
	}
}
