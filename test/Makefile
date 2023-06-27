CC=avr-gcc
OBJCOPY=avr-objcopy

TARGET=main
OBJECTS= main.o kernel.o mutex.o pls7.o profiler.o queue.o sema.o task.o usart.o pin.o
PORT=COM8

$(TARGET).hex:	$(TARGET).elf
	${OBJCOPY} -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf:	$(OBJECTS)
	${CC} -mmcu=atmega328p -o $(TARGET).elf $(OBJECTS)

%.o : %.c
	${CC} -Os -DF_CPU=16000000UL -mmcu=atmega328p -c $< -o $@
	
program: $(TARGET).hex
	avrdude -c arduino -p ATMEGA328P -P ${PORT} -b 115200 -U flash:w:$(TARGET).hex
	
clean:
	rm *.o *.elf *.hex