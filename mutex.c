#include "kernel.h"
#include "mutex.h"
#include "pin.h"
#include "usart.h"

// Konstanta koja omogucava upotrebu muteksa
#define USE_MUTEX

OSMutex mutex; // Kreiranje objekata za muteks

void task1(void *p)
{
	uint8_t i;
	int8_t msg[64];
	
	while(1)
	{
		#ifdef USE_MUTEX
		OSTakeMutex(&mutex); // Zauzimanje muteksa
		#endif
		
		// Ispis poruke
		for(i = 0; i < 3; i++)
		{
			sprintf(msg, "Task1: %d\r\n", i);
			usartPutString(msg);
			OSSleep(200);
		}
		
		#ifdef USE_MUTEX
		OSGiveMutex(&mutex); // Oslobadjanje muteksa
		#endif
	}
}

void task2(void *p)
{
	uint8_t i;
	int8_t msg[64];
	
	while(1)
	{
		#ifdef USE_MUTEX
		OSTakeMutex(&mutex); // Zauzimanje muteksa
		#endif
		
		// Ispis poruke
		for(i = 0; i < 3; i++)
		{
			sprintf(msg, "Task2: %d\r\n", i);
			usartPutString(msg);
			OSSleep(200);
		}
		
		#ifdef USE_MUTEX
		OSGiveMutex(&mutex); // Oslobadjanje muteksa
		#endif
	}
}

void task3(void *p)
{
	uint8_t i;
	int8_t msg[64];
	
	while(1)
	{
		#ifdef USE_MUTEX
		OSTakeMutex(&mutex); // Zauzimanje muteksa
		#endif
		
		// Ispis poruke
		for(i = 0; i < 3; i++)
		{
			sprintf(msg, "Task3: %d\r\n", i);
			usartPutString(msg);
			OSSleep(200);
		}
		
		#ifdef USE_MUTEX
		OSGiveMutex(&mutex); // Oslobadjanje muteksa
		#endif
	}
}

void task4(void *p)
{
	// Treptanje diode
	while(1)
	{
		pinSetValue(PORT_B, 5, HIGH);
		OSSleep(500);
		pinSetValue(PORT_B, 5, LOW);
		OSSleep(500);
	}
}

int16_t main()
{
	// Inicijalizacija pina koji upravlja LED diodom i serijske komunikacije
	pinInit(PORT_B, 5, OUTPUT);
	usartInit(115200);
	
	OSInit(4); // Inicijalizacija operativnog sistema sa dva zadatka
	
	// Inicijalizacija muteksa
	OSCreateMutex(&mutex);
	
	// Inicijalziacija zadataka
	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);
	OSCreateTask(2, task3, 0);
	OSCreateTask(3, task4, 0);
	
	OSRun(); // Pokretanje operativnog sistema
	
	while(1);
}