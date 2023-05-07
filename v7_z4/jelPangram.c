#include "usart.h"
#include "jelPangram.h"

bool jelPangram(int8_t *s)
{
	int8_t tmp[26];
	int8_t p = 1;

	for (int8_t i = 0; i != 26; i++)
		tmp[i] = 0;

	while (*s != 0)
	{
		for (int8_t i = 0; i != 26; i++)
		{
			if (*s == 97 + i || *s == 65 + i)
				tmp[i] = 1;
		}

		s++;
	}

	for (int8_t i = 0; i != 26; i++)
		p &= tmp[i];

	if (p)
		return true;
	else
		return false;
}

