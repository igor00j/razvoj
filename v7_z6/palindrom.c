#include "palindrom.h"

bool palindrom(int8_t *s)
{
	int8_t len = strlen(s);

	for (int8_t i = 0; i < len/2; i++)
	{
		if(s[i] != s[len - 1 - i])
			return false;
	}
	return true;
}

void podPalindrom(int8_t *s)
{
	int8_t len = strlen(s);
	int8_t tmp[64];
	int8_t p = 1;

	for (int8_t duz = len; duz != 0; duz--)
	{
		for (int8_t i = 0; i != len - duz +1; i++)
		{
			for (int8_t j = i; j < i + duz/2; j++)
			{
				if (s[j] != s[i + duz - 1 + i - j])
					p = 0;
			}

			if (p)
			{
				for (int8_t k = 0; k != duz; k++)
					tmp[k] = s[k + i];
				tmp[duz] = 0;
				usartPutString(tmp);
				return;
			}
			else
				p = 1;
		}
	}
}
