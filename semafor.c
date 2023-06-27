#include "kernel.h"
#include "sema.h"
#include "pin.h"
#include "usart.h"

OSSema sem; // Kreiranje objetka za semafor

void task1(void *p)
{
	// Ucitavanje parametra
	uint16_t ms = (uint16_t)p;
	ms = ms/2;
	uint8_t i;
	while(1)
	{
		OSTakeSema(&sem); // Zauzimanje semafora
		
		// Treptanje diode
		pinSetValue(PORT_B, 5, HIGH);
		OSSleep(ms);
		pinSetValue(PORT_B, 5, LOW);
		OSSleep(ms);
	}
}

void task2(void *p)
{
	int8_t msg[64];
	uint8_t msg_len;
	int8_t start_msg[] = "START";
	uint8_t flag;
	uint8_t i;
	
	while(1)
	{
		// Ucitavanje poruke
		usartPutString("Type \"START\" to enable LED pulsing!\r\n");
		while(usartAvailable() == 0)
			OSSleep(10);
		OSSleep(100);
		
		msg_len = usartGetString(msg);
		
		// Provera da li je poruka validna
		if(msg_len == 5)
		{
			flag = 0;
			for(i = 0; i < 5; i++)
			{
				if(msg[i] != start_msg[i])
					flag = 1;
			}
			if(flag == 0)
			{
				usartPutString("SUCCESS!\r\n");
				OSGiveSema(&sem); // Oslobadjanje semafora
			}
			else
				usartPutString("FAIL!\r\n");
		}
		else
			usartPutString("FAIL!\r\n");
	}
}

int16_t main()
{
	// Inicijalizacija pina koji upravlja LED diodom i serijske komunikacije
	pinInit(PORT_B, 5, OUTPUT);
	usartInit(115200);
	usartPutString("Test!\r\n");

	OSInit(2); // Inicijalizacija operativnog sistema sa dva zadatka

	OSCreateSema(&sem, 0, 0); // Inicijalizacija semafora

	// Inicijalziacija zadataka
	OSCreateTask(0, task1, (void *) 1000);
	OSCreateTask(1, task2, 0);

	OSRun(); // Pokretanje operativnog sistema

	while(1);
}
