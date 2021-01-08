#pragma once

const int REGISTER_SIZE_8_BIT = 8;
const int REGISTER_SIZE_16_BIT = 16;

struct Register {
	int size;
	int value;
};

void register_init(struct Register*, int, int);
void set_register_value(struct Register *, int);