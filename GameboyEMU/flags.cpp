#include <stdlib.h>

#include "flags.h"

bool* flags;

void flags_init() {
	flags = (bool*)malloc(sizeof(bool) * FLAG_COUNT);
	for (int i = 0; i < FLAG_COUNT; i++)
		flags[i] = 0;
}

void clear_flag(int flag) {
	flags[flag] = 0;
}

void set_flag(int flag) {
	flags[flag] = 1;
}

void flip_flag(int flag) {
	flags[flag] = !flags[flag];
}

bool flag_set(int flag) {
	return flags[flag];
}