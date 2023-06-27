#include <stdio.h>
#include "kernel.h"
#include "mutex.h"
#include "pin.h"
#include "usart.h"

// Kreiranje objekata za muteks i uslovne promenljive
OSMutex mutex;
OSCond cv_full, cv_empty;

// Kreiranje buffera
#define BUFFER_SIZE 4
int8_t buffer[BUFFER_SIZE];
uint8_t head_ptr = 0, back_ptr = 0;
uint8_t count = 0;

// Deklaracije funkcija za upravljanje baferom
void add(int8_t c);
int8_t remove();

void task1(void *p)
{
	int8_t msg[64];
	int8_t i;
	
	while(1)
	{		
		for(i = 0; i < 12; i++)
		{
			OSTakeMutex(&mutex); // Zauzimanje muteksa

			// Cekanje na pojavu signala da je element uklonjen
			while(count == BUFFER_SIZE)
				OSWait(&cv_full, &mutex);
			
			add(i); // Dodavanje elementa u bafer
			
			// Ispis dodate vrednosti
			sprintf(msg, "Added %d\r\n", i);
			usartPutString(msg);
			
			OSSignal(&cv_empty); // Signali da je element dodat
			
			OSGiveMutex(&mutex); // Oslobadjanje muteksa

			// Pauza za potrebe tesitranja
			OSSleep(200);
		}
		
		// Pauza za potrebe tesitranja
		OSSleep(2000);
	}
}

void task2(void *p)
{
	int8_t c;
	int8_t msg[64];
	int8_t i = 0;
	
	// Pauza za potrebe tesitranja
	OSSleep(3000);
	
	while(1)
	{
		OSTakeMutex(&mutex); // Zauzimanje muteksa
		
		// Cekanje na pojavu signala da je element dodat
		while(count == 0)
			OSWait(&cv_empty, &mutex);
		
		c = remove(); // Uklanjanje elementa iz bafera

		// Ispis uklonjenje vrednosti
		sprintf(msg, "Removed %d\r\n", c);
		usartPutString(msg);

		OSSignal(&cv_full); // Signali da je element uklonjen
		
		OSGiveMutex(&mutex); // Oslobadjanje muteksa
		
		// Pauze za potrebe tesitranja
		i++;
		if(i % 7 == 0)
			OSSleep(2000);
		
		OSSleep(100);
	}
}

void task3(void *p)
{
	// Treperenje diode
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

	OSInit(3); // Inicijalizacija operativnog sistema sa tri zadatka

	// Inicijalizacija muteksa i uslovnih promenljivih
	OSCreateMutex(&mutex);
	OSCreateConditional(&cv_full);
	OSCreateConditional(&cv_empty);

	// Inicijalziacija zadataka
	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);
	OSCreateTask(2, task3, 0);

	OSRun(); // Pokretanje operativnog sistema

	while(1);
}

// Definicija funkcije za dodavanje elementa u bafer
void add(int8_t c)
{
	buffer[head_ptr] = c;
	head_ptr = (head_ptr + 1) % BUFFER_SIZE;
	count++;
}

// Definicija funkcije za uklanjanje elementa iz bafera
int8_t remove()
{
	int8_t tmp = buffer[back_ptr];
	back_ptr = (back_ptr + 1) % BUFFER_SIZE;
	count--;
	
	return tmp;
}