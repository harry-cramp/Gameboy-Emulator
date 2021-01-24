// Author: Harry Cramp
// Date: January 2021

#define GLFW_INCLUDE_NONE

#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "glfw3dll.lib")

#include <iostream>
#include <glfw3.h>
#include <time.h>

#include "memory.h"
#include "flags.h"
#include "opcodes.h"
#include "processor.h"

using namespace std;

void system_init() {
	memory_init();
	flags_init();
	processor_init();
}

void delay(int seconds) {
	int now = time(NULL);
	while (time(NULL) < now + seconds);
}

int main() {
	system_init();

	dump_register_values();
	delay(4);
	cout << "LOADING DATA [69] TO ADDRESS [0x420]" << endl;
	set_data(0x420, 69);
	delay(4);
	cout << "EXECUTING INSTRUCTION 0x46 - LOAD DATA AT ADDRESS (HL) TO REGISTER B" << endl;
	execute(0b01000110);
	delay(4);
	dump_register_values();

	return 0;
}