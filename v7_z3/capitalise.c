#include "capitalise.h"

void capitalise(int8_t *s)
{
	while (*s != 0)
	{
		if (*s >= 97 && *s <= 122)
			*s -= 32;
		s++;
	}
}
