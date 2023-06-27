#include "kernel.h"
#include "sema.h"
#include "pls7.h"
#include <avr/interrupt.h>

void task1(void *p)
{
	while(1)
	{
		writeDisplay(LEDS, 0xff);
		OSSleep(500);
		writeDisplay(LEDS, 0x00);
		OSSleep(500);
	}
}

OSSema sem;

ISR(PCINT1_vect)
{
	OSGiveSema(&sem);
}

void task2(void *p)
{
	writeDisplay(D1, 0xfe);
	writeDisplay(D2, 0xfe);
	writeDisplay(D3, 0xfe);
	writeDisplay(D4, 0xfe);

	while(1)
	{
		OSTakeSema(&sem);

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

	PCMSK1 = 0x0f;
	PCICR = 0x02;

	OSInit(2);

	OSCreateSema(&sem, 0, 1);

	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);

	OSRun();

	while(1);
}
