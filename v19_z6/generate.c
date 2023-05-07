#include <stdlib.h>
#include "generate.h"

#define UPPER 9
#define LOWER 5

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
