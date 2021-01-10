#pragma once

const int RAM_SIZE = 8192;

extern int* contents;

void memory_init();
int get_data(int address);
void set_data(int address, int data);