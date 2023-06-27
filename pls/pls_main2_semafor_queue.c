#include "kernel.h"
#include "queue.h"
#include "sema.h"
#include "pls7.h"
#include <avr/interrupt.h>

#define QLEN 8
int16_t qbuff_7seg[QLEN];
int16_t qbuff_LED[QLEN];
OSQueue queue_7seg;
OSQueue queue_LED;
OSSema sem;

const uint8_t simboli[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14};


ISR(PCINT1_vect)
{
	OSGiveSema(&sem);
}

void task1(void *p)
{
	int16_t sw;
	while(1)
	{
		OSTakeSema(&sem);

		if (buttonState(LEFT))
		{
			sw = readSwitches();
			OSEnqueue(sw, &queue_7seg);
			OSEnqueue(sw, &queue_LED);
		}
	}
}

void task2(void *p)
{
	uint8_t sw;
	while(1)
	{
		sw = (uint8_t) OSDequeue(&queue_LED);
		writeDisplay(LEDS, sw);
	}
}

void task3(void *p)
{
	uint8_t sw;
	while(1)
	{
		sw = ~((uint8_t) OSDequeue(&queue_7seg));
		writeDisplay(D1, simboli[0]);
		writeDisplay(D2, simboli[(sw / 100) % 10]);
		writeDisplay(D3, simboli[(sw / 10) % 10]);
		writeDisplay(D4, simboli[sw % 10]);
	}
}

int16_t main()
{
	init();

	PCMSK1 = 0x0f;
	PCICR = 0x02;

	OSInit(3);

	OSCreateQueue(qbuff_7seg, QLEN, &queue_7seg);
	OSCreateQueue(qbuff_LED, QLEN, &queue_LED);

	OSCreateSema(&sem, 0, 1);

	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);
	OSCreateTask(2, task3, 0);

	OSRun();

	while(1);
}
