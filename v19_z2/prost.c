#include "prost.h"

bool isPrime(uint32_t  n)
{
	if (n == 1)
		return 0;

	for (uint32_t i = 2; i <= n/2; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}

	return 1;
}
