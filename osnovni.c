#include <stdio.h>
#include "kernel.h"
#include "pin.h"
#include "usart.h"

// Prvi zadatak
void task1(void *p)
{
	// Ucitavanje parametra
	uint16_t ms = (uint16_t)p;
	ms = ms/2;
	
	// Treperenje diode
	while(1)
	{
		pinSetValue(PORT_B, 5, HIGH);
		OSSleep(ms);
		pinSetValue(PORT_B, 5, LOW);
		OSSleep(ms);
	}
}

// Drugi zadatak
void task2(void *p)
{
	// Ucitavanje parametra
	int8_t msg[64];
	uint16_t ms = (uint16_t)p;
	
	// Slanje poruke putem serijskog porta
	while(1)
	{
		OSSleep(ms);
		sprintf(msg, "Task2: %ulms\r\n", OSticks());
		usartPutString(msg);
	}
}

int16_t main()
{
	// Inicijalizacija pina koji upravlja LED diodom i serijske komunikacije
	pinInit(PORT_B, 5, OUTPUT);
	usartInit(115200);
	
	OSInit(2); // Inicijalizacija operativnog sistema sa dva zadatka

	// Inicijalziacija zadataka
	OSCreateTask(0, task1, (void *) 1000);
	OSCreateTask(1, task2, (void *) 500);

	OSRun(); // Pokretanje operativnog sistema

	while(1);
}
