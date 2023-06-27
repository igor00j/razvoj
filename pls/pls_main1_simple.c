#include "kernel.h"
#include "pls7.h"


void task1(void *p)
{
	while(1)
	{
		writeDisplay(LEDS, 0xaa);
		OSSleep(500);
		writeDisplay(LEDS, 0x55);
		OSSleep(500);
	}
}

void task2(void *p)
{
	while(1)
	{
		OSSleep(50);

		if (buttonState(LEFT))
			writeDisplay(D1, 0x0c);
		else
			writeDisplay(D1, 0xfe);

		if (buttonState(DOWN))
			writeDisplay(D2, 0xa4);
		else
			writeDisplay(D2, 0xfe);

		if (buttonState(RIGHT))
			writeDisplay(D3, 0x27);
		else
			writeDisplay(D3, 0xfe);

		if (buttonState(UP))
			writeDisplay(D4, 0xc4);
		else
			writeDisplay(D4, 0xfe);
	}
}

int16_t main()
{
	init();
	OSInit(2);

	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);

	OSRun();

	while(1);
}
