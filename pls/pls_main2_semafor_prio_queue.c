#include "kernel.h"
#include "queue.h"
#include "sema.h"
#include "pls7.h"
#include <avr/interrupt.h>

#define QLEN 8
TPrioNode qbuff_7seg[QLEN];
OSQueue queue_7seg;
OSSema sem;

const uint8_t simboli[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14};


ISR(PCINT1_vect)
{
	OSGiveSema(&sem);
}

void task1(void *p)
{
	int16_t sw;
	uint8_t i;
	while(1)
	{
		OSTakeSema(&sem);

		if (buttonState(LEFT))
		{
			for(i = 5; i > 0; i--)
			{
				OSPrioEnqueue(i, 1, &queue_7seg);
				OSSleep(10);
			}
		}
		else if (buttonState(RIGHT))
		{
			OSPrioEnqueue(10, 0, &queue_7seg);
		}
	}
}

void task2(void *p)
{
	uint8_t sw;
	while(1)
	{
		sw = (uint8_t) OSDequeue(&queue_7seg);
		writeDisplay(D1, simboli[0]);
		writeDisplay(D2, simboli[(sw / 100) % 10]);
		writeDisplay(D3, simboli[(sw / 10) % 10]);
		writeDisplay(D4, simboli[sw % 10]);
		OSSleep(1000);
	}
}

int16_t main()
{
	init();

	PCMSK1 = 0x0f;
	PCICR = 0x02;

	OSInit(3);

	OSCreatePrioQueue(qbuff_7seg, QLEN, &queue_7seg);

	OSCreateSema(&sem, 0, 1);

	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);

	OSRun();

	while(1);
}
