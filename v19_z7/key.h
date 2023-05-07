/*
 * key.h
 *
 *  Created on: 18.04.2022.
 *      Author: Korisnik
 */

#ifndef KEY_H_
#define KEY_H_

#include <stdint.h>
#include <stdbool.h>
#include "usart.h"
#include "keypad.h"

void timerOn();

void keyOpeartion(uint8_t key, uint8_t *keys, uint8_t keys_l, uint8_t *target);

#endif /* KEY_H_ */
