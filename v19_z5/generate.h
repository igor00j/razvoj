#ifndef GENERATE_H_
#define GENERATE_H_

#include <stdint.h>
#include <stdbool.h>

void generateCode(uint8_t *code);

bool matching(uint8_t *a, uint8_t la, uint8_t *b, uint8_t lb);

#endif /* GENERATE_H_ */
