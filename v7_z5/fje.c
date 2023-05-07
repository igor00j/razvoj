#include "fje.h"

void ucitajDragulje(int8_t *s)
{
	int8_t len = 0;
	do
	{
		s[len++] = usartGetChar();
	} while (s[len - 1] != 58);

	s[len - 1] = 0;
}

int8_t prebrojDragulje(int8_t *dra, int8_t *kam)
{
	int8_t dlen = strlen(dra);
	int8_t klen = strlen(kam);
	int8_t br = 0;

	for (int8_t i = 0; i != dlen; i++)
	{
		for (int8_t j = 0; j != klen; j++)
			{
				if (kam[j] == dra[i])
					br++;
			}
	}

	return br;
}

void ispis(int8_t c)
{
	int8_t str[64];
	int8_t tmp = 0;
	sprintf(str, "%d", c);
	while(str[tmp] != 0)
	{
		usartPutChar(str[tmp]);
		tmp++;
	}
}
