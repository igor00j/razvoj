#include <avr/io.h>
#include <string.h>
#include "key.h"
#include "generate.h"

#define NUM_OF_KEYS 10
#define MAX_SYMBOLS 5

uint8_t keys[NUM_OF_KEYS][MAX_SYMBOLS] = {"0", "1", "2abc", "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9wxyz"};
uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	timerOn();
	usartInit(9600);
	keypadInit(rows, cols);

	uint8_t button_old = 0x00 , button_new = 0x00;

	uint8_t gen_code[64];
	for (uint8_t i = 0; i != 64; i++)
		gen_code[i] = 0;
	uint8_t input_code[64];
	for (uint8_t i = 0; i != 64; i++)
		input_code[i] = 0;

	uint8_t cond = 0;
	uint8_t tmp = 0;
	uint8_t res[2];

	uint8_t gen_l = 0, input_l = 0;

	while (1)
	{
		if (!cond)
		{
			generateCode(gen_code);
			usartPutString(gen_code);
			usartPutChar('\r');
			cond = 1;
		}

		button_new = keypadScan();
		if (button_new != 0x00 && button_new != button_old)
		{
			if (button_new >= '0' && button_new <= '9')
			{
				keyOperation(button_new - '0', keys[button_new -'0'], strlen(keys[button_new - '0']), res);

				if (res[0])
					tmp--;

				input_code[tmp] = res[1];
				tmp++;
			}
			else if(button_new == '*')
			{
				gen_l = strlen(gen_code);
				input_l = strlen(input_code);

				usartPutChar('\r');
				if (matching(gen_code, gen_l, input_code, input_l))
					usartPutString("Ispravno unet kod\r\r");
				else
					usartPutString("Neispravno unet kod\r\r");

				for (uint8_t i = 0; i != gen_l; i++)
					gen_code[i] = 0;
				for (uint8_t i = 0; i != input_l; i++)
					input_code[i] = 0;

				cond = 0;
				tmp = 0;
			}
		}

		button_old = button_new;
	}
}
