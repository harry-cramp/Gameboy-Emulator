#include <math.h>

#include "register.h"

void register_init(struct Register* reg, int size, int value) {
	reg->size = size;
	reg->value = value;
}

int get_lower_register_value(struct Register reg) {
	return reg.value & 0xFF;
}

int get_upper_register_value(struct Register reg) {
	return (reg.value & 0xFF00) >> 8;
}

void set_register_value(struct Register* reg, int value) {
	int register_size = reg->size;
	if (value < 0)
		value = 0;
	value &= ((int)pow(2.0, (double)register_size) - 1);
	reg->value = value;
}