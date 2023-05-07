#include <avr/io.h>
#include <stdint.h>

void logTran(state_t state, state t next_state);

void logTime(uint16_t mm, uint16_t ss);

void logCut();

void ledOff();

void ledOn();

void ledBlink();