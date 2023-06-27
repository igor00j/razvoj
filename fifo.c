#include "kernel.h"
#include "queue.h"
#include "pin.h"
#include "usart.h"

// Kreiranje objekata za red
#define QLEN 20
int16_t qbuff[QLEN];
OSQueue queue;

void task1(void *p)
{
	int16_t num_of_pulses;
	int16_t pulse_period;
	int8_t tmp[128];
	
	while(1)
	{
		// Ucitavanje poruke
		do 
		{
			usartPutString("Start pulsing by typing \"<num_of_pulses>X<pulse_period>\"!\r\n");
			while(usartAvailable() == 0)
				OSSleep(10);
			OSSleep(100);
			
			num_of_pulses = usartParseInt();
			pulse_period = usartParseInt();
			
		} while((num_of_pulses <= 0) || (num_of_pulses > 9) || (pulse_period <= 0) || (pulse_period > 2000));
		
		// Dodavanje parametara treptanja u red
		OSEnqueue(num_of_pulses, &queue);
		OSEnqueue(pulse_period, &queue);
		
		// Ispis poruke o uspesnom dodavanju treptanja
		sprintf(tmp, "Added %d pulses with period %dms!\r\n", num_of_pulses, pulse_period);
		usartPutString(tmp);
	}
}

void task2(void *p)
{
	int16_t num_of_pulses;
	int16_t pulse_period;
	uint8_t i;
	
	while(1)
	{
		// Uklanjanje parametara treptanja iz reda
		num_of_pulses = OSDequeue(&queue);
		pulse_period = OSDequeue(&queue);
		
		// Treptanje diode
		for(i = 0; i < num_of_pulses; i++)
		{
			pinSetValue(PORT_B, 5, HIGH);
			OSSleep(pulse_period/2);
			pinSetValue(PORT_B, 5, LOW);
			OSSleep(pulse_period/2);
		}
	}
}

int16_t main()
{
	// Inicijalizacija pina koji upravlja LED diodom i serijske komunikacije
	pinInit(PORT_B, 5, OUTPUT);
	usartInit(115200);

	OSInit(2); // Inicijalizacija operativnog sistema sa dva zadatka

	// Inicijalizacija reda
	OSCreateQueue(qbuff, QLEN, &queue);

	// Inicijalziacija zadataka
	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);

	OSRun(); // Pokretanje operativnog sistema

	while(1);
}
