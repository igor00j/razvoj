#include <stdlib.h>
#include "generate.h"

#define UPPER 9
#define LOWER 5

void generateCode(uint8_t *code)
{
	uint8_t length = (rand() % (UPPER - LOWER + 1)) + LOWER;

	for (uint8_t i = 0; i != length;)
	{
		if (rand() % 2)
			*code = rand() % ('9' - '0' + 1) + '0';
		else
			*code = rand() % ('z' - 'a' + 1) + 'a';

		i++;
		code++;
	}
}

bool matching(uint8_t *a, uint8_t a_l, uint8_t *b, uint8_t b_l)
{
	if (a_l != b_l)
		return false;

	for (uint8_t i = 0; i != a_l - 1;)
	{
		if (*a != *b)
			return false;

		i++;
		a++;
		b++;
	}

	return true;
}
