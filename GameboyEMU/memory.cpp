#include <stdlib.h>

#include "memory.h"

int* contents;

// Memory specifications:
// RAM:		8 Kilobytes (8192 bytes)
void memory_init() {
	contents = (int*)malloc(sizeof(int) * RAM_SIZE);
}

int get_data(int address) {
	return contents[address];
}

void set_data(int address, int data) {
	contents[address] = data;
}