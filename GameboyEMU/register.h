#pragma once

const int REGISTER_SIZE_8_BIT = 8;
const int REGISTER_SIZE_16_BIT = 16;

struct Register {
	int size;
	int value;
};

void register_init(struct Register*, int, int);
int get_upper_register_value(struct Register);
int get_lower_register_value(struct Register);
void set_register_value(struct Register *, int);
void decrement_register(struct Register*);
void increment_register(struct Register*);
void load_to_upper(struct Register*, int data);
void load_to_lower(struct Register*, int data);