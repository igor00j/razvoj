#include <stdio.h>
#include <avr/io.h>
#include "lucky.h"

int8_t isLucky(int16_t num)
{
	if (num % 2 == 0)
	{
		return 0;
	}

	int8_t brojevi[num];
	int8_t tmp;

	for (int8_t i = 1; i < num + 1; i++)
	{
		if (i % 2 == 0)
			brojevi[i - 1] = 0;
		else
			brojevi[i - 1] = 1;
	}

	int8_t rb = num - num/2;

	for (int8_t i = 3; i < num + 1; i++)
	{
		if (brojevi[i - 1] == 1)
		{
			if (rb == i)
			{
				return 0;
			}
			else if (rb < i)
			{
				return brojevi[num - 1];
			}

			tmp = 0;

			for (int8_t j = 1; j < num + 1; j++)
			{
				if (brojevi[j - 1] == 1)
				{
					tmp++;
					if (tmp == i)
					{
						brojevi[j - 1] = 0;
						tmp = 0;
					}
				}
			}

			rb = rb - rb/i;
		}
	}

	return brojevi[num - 1];
}
