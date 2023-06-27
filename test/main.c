#include "kernel.h"
#include "mutex.h"
#include "pls7.h"

#define USE_CV

const uint8_t simboli[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14};

OSMutex mutex;
OSCond cv1, cv2, cv3;

void task1(void *p)
{
	uint8_t tmp;
	while(1)
	{
		writeDisplay(D1, 0xfe);

		tmp = 0x80;

		while(tmp != 0)
		{
			writeDisplay(LEDS, ~tmp);
			tmp >>= 1;
			OSSleep(100);
		}

		writeDisplay(D1, 0xff);

		#ifdef USE_CV
		OSSignal(&cv3);
		OSWait(&cv1, &mutex);
		#endif
	}
}

void task2(void *p)
{
	uint8_t tmp;
	while(1)
	{
		#ifdef USE_CV
		OSWait(&cv2, &mutex);
		#endif
		
		writeDisplay(D2, 0xfe);

		tmp = 0x01;

		while(tmp != 0)
		{
			writeDisplay(LEDS, ~tmp);
			tmp <<= 1;
			OSSleep(100);
		}

		writeDisplay(D2, 0xff);
		
		#ifdef USE_CV
		OSSignal(&cv1);
		#endif
	}
}

void task3(void *p)
{
	uint8_t tmp;
	uint8_t i;
	while(1)
	{
		#ifdef USE_CV
		OSWait(&cv3, &mutex);
		#endif
		
		writeDisplay(D3, 0xfe);

		tmp = 0xaa;

		for(i = 0; i < 8; i++)
		{
			writeDisplay(LEDS, tmp);
			tmp = ~tmp;
			OSSleep(100);
		}

		writeDisplay(D3, 0xff);
		
		#ifdef USE_CV
		OSSignal(&cv2);
		#endif
	}
}

void task4(void *p)
{
	uint8_t tmp = 0;;
	while(1)
	{
		writeDisplay(D4, simboli[tmp]);

		tmp++;
		if(tmp == 10)
			tmp = 0;

		OSSleep(100);
	}
}

int16_t main()
{
	init();

	OSInit(4);

	OSCreateMutex(&mutex);
	
	OSCreateConditional(&cv1);
	OSCreateConditional(&cv2);
	OSCreateConditional(&cv3);

	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);
	OSCreateTask(2, task3, 0);
	OSCreateTask(3, task4, 0);

	OSRun();

	while(1);
}
