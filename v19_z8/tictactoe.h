#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <stdbool.h>
#include "usart.h"

void displayTable(uint8_t *table1, uint8_t *table2, uint8_t *table3);

void resetTable(uint8_t *table1, uint8_t *table2, uint8_t *table3);

bool turn(uint8_t *table1, uint8_t *table2, uint8_t *table3, uint8_t button, uint8_t player);

bool endGame(uint8_t *table1, uint8_t *table2, uint8_t *table3, uint8_t player);

#endif /* TICTACTOE_H_ */
