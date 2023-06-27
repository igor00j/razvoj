#include "kernel.h"
#include "queue.h"
#include "pin.h"
#include "usart.h"

// Kreiranje objekata za redove
#define QLEN 8
TPrioNode qbuff_num_of_pulses[QLEN];
TPrioNode qbuff_pulse_period[QLEN];
OSQueue queue_num_of_pulses;
OSQueue queue_pulse_period;

void task1(void *p)
{
	int16_t num_of_pulses;
	int16_t pulse_period;
	int8_t tmp[128];
	int8_t priority;
	
	while(1)
	{
		// Ucitavanje poruke
		do 
		{
			usartPutString("Start pulsing by typing \"<type><num_of_pulses>X<pulse_period>\"!\r\n");
			while(usartAvailable() == 0)
				OSSleep(10);
			OSSleep(100);
			
			priority = usartGetChar();
			num_of_pulses = usartParseInt();
			pulse_period = usartParseInt();
			
		} while((num_of_pulses <= 0) || (num_of_pulses > 9) || (pulse_period <= 0) || (pulse_period > 2000) || ((priority != 'S') && (priority != 'P')));
		
		// Dodavanje parametara treptanja u redove
		if(priority == 'P')
		{
			OSPrioEnqueue(num_of_pulses, 0, &queue_num_of_pulses);
			OSPrioEnqueue(pulse_period, 0, &queue_pulse_period);
			// Ispis poruke o prioritetnom dodavanju treptanja
			sprintf(tmp, "Added priority %d pulses with period %dms!\r\n", num_of_pulses, pulse_period);
			usartPutString(tmp);
		}
		else
		{
			OSPrioEnqueue(num_of_pulses, 1, &queue_num_of_pulses);
			OSPrioEnqueue(pulse_period, 1, &queue_pulse_period);
			// Ispis poruke o standardnom dodavanju treptanja
			sprintf(tmp, "Added standard %d pulses with period %dms!\r\n", num_of_pulses, pulse_period);
			usartPutString(tmp);
		}
	}
}

void task2(void *p)
{
	int16_t num_of_pulses;
	int16_t pulse_period;
	uint8_t i;
	
	while(1)
	{
		// Uklanjanje parametara treptanja iz redova
		num_of_pulses = OSDequeue(&queue_num_of_pulses);
		pulse_period = OSDequeue(&queue_pulse_period);
		
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
	OSCreatePrioQueue(qbuff_num_of_pulses, QLEN, &queue_num_of_pulses);
	OSCreatePrioQueue(qbuff_pulse_period, QLEN, &queue_pulse_period);

	// Inicijalziacija zadataka
	OSCreateTask(0, task1, 0);
	OSCreateTask(1, task2, 0);

	OSRun(); // Pokretanje operativnog sistema

	while(1);
}
