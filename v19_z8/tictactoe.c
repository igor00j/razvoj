#include "tictactoe.h"

void displayTable(uint8_t *table1, uint8_t *table2, uint8_t *table3)
{
	usartPutChar('|');

	for (int8_t i = 0; i < 3; i++)
	{
		usartPutChar(*(table1 + i));
		usartPutChar('|');
	}

	usartPutChar('\r');
	usartPutChar('|');

	for (int8_t i = 0; i < 3; i++)
	{
		usartPutChar(*(table2 + i));
		usartPutChar('|');
	}

	usartPutChar('\r');
	usartPutChar('|');

	for (int8_t i = 0; i < 3; i++)
	{
		usartPutChar(*(table3 + i));
		usartPutChar('|');
	}

	usartPutChar('\r');
	usartPutString("-------");
	usartPutChar('\r');
}

void resetTable(uint8_t *table1, uint8_t *table2, uint8_t *table3)
{
	for (int8_t i = 0; i < 3; i++)
		*(table1 + i) = '_';

	for (int8_t i = 0; i < 3; i++)
		*(table2 + i) = '_';

	for (int8_t i = 0; i < 3; i++)
		*(table3 + i) = '_';
}

bool turn(uint8_t *table1, uint8_t *table2, uint8_t *table3, uint8_t button, uint8_t player)
{
	switch (button)
	{
		case '1':
			if (*table1 == '_')
			{
				*table1 = player;
				return true;
			}
			else
				return false;

		case '2':
			if (*(table1 + 1) == '_')
			{
				*(table1 + 1) = player;
				return true;
			}
			else
				return false;

		case '3':
			if (*(table1 + 2) == '_')
			{
				*(table1 + 2) = player;
				return true;
			}
			else
				return false;

		case '4':
			if (*table2 == '_')
			{
				*table2 = player;
				return true;
			}
			else
				return false;

		case '5':
			if (*(table2 + 1) == '_')
			{
				*(table2 + 1) = player;
				return true;
			}
			else
				return false;

		case '6':
			if (*(table2 + 2) == '_')
			{
				*(table2 + 2) = player;
				return true;
			}
			else
				return false;

		case '7':
			if (*table3 == '_')
			{
				*table3 = player;
				return true;
			}
			else
				return false;

		case '8':
			if (*(table3 + 1) == '_')
			{
				*(table3 + 1) = player;
				return true;
			}
			else
				return false;

		case '9':
			if (*(table3 + 2) == '_')
			{
				*(table3 + 2) = player;
				return true;
			}
			else
				return false;
	}
}

bool endGame(uint8_t *table1, uint8_t *table2, uint8_t *table3, uint8_t player)
{
	if ((*table1 == *(table1 + 1) && *table1 == *(table1 + 2) && *table1 == player)
		 || (*table2 == *(table2 + 1) && *table2 == *(table2 + 2) && *table2 == player)
		 || (*table3 == *(table3 + 1) && *table3 == *(table3 + 2) && *table3 == player)
		 || (*table1 == *table2 && *table1 == *table3 && *table1 == player)
		 || (*(table1 + 1) == *(table2 + 1) && *(table1 + 1) == *(table3 + 1) && *(table1 + 1) == player)
		 || (*(table1 + 2) == *(table2 + 2) && *(table1 + 2) == *(table3 + 2) && *(table1 + 2) == player)
		 || (*table1 == *(table2 + 1) && *table1 == *(table3 + 2) && *table1 == player)
		 || (*table3 == *(table2 + 1) && *table3 == *(table1 + 2) && *table3 == player))
	{
		usartPutString("Pobednik je ");
		usartPutChar(player);
		usartPutChar('\r');

		return true;
	}

	else if ((*table1 != '_') && (*table2 != '_') && (*table3 != '_')
			&& (*(table1 + 1) != '_') && (*(table2 + 1) != '_') && (*(table3 + 1) != '_')
			&& (*(table1 + 2) != '_') && (*(table2 + 2) != '_') && (*(table3 + 2) != '_'))
	{
		usartPutString("Nema pobednika");
		usartPutChar('\r');

		return true;
	}

	return false;
}
