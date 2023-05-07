#ifndef GHERO_H_
#define GHERO_H_

#include <stdint.h>
#include <stdbool.h>
#include "usart.h"
#include "keypad.h"

void timerOn();

uint8_t symGen();

void ghDisplay(uint32_t lives, uint32_t points, uint32_t interval, uint32_t counter);

void ghOperation(uint8_t gen_sym, uint8_t button, uint32_t *lives, uint32_t *points, uint32_t *interval, uint32_t *counter);

void ghResult(uint32_t *lives, uint32_t *points, uint32_t *interval, uint32_t *counter);

#endif /* GHERO_H_ */
