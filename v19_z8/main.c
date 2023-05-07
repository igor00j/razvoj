#include <avr/io.h>
#include "usart.h"
#include "keypad.h"
#include "tictactoe.h"

#define PLAYER_ONE 'x'
#define PLAYER_TWO 'o'

uint8_t tic_tac_toe[3][32] = {"___", "___", "___"};
uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	usartInit(9600);
	keypadInit(rows, cols);

	uint8_t button_new, button_old;
	uint8_t cond = 1;
	uint8_t player;

	displayTable(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2]);

	while (1)
	{
		button_new = keypadScan();

		if (button_new >= '1' && button_new <= '9' && button_new != button_old)
		{
			switch (cond)
			{
				case 1:
					player = 'x';
					if (turn(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2], button_new, player))
						cond = 2;
					break;
				case 2:
					player = 'o';
					if (turn(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2], button_new, player))
						cond = 1;
					break;
			}

			displayTable(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2]);

			if(endGame(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2], player))
			{
				resetTable(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2]);
				displayTable(tic_tac_toe[0], tic_tac_toe[1], tic_tac_toe[2]);
				cond = 1;
			}
		}

		button_old = button_new;
	}
}
