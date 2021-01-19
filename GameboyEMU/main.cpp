// Author: Harry Cramp
// Date: January 2021

#define GLFW_INCLUDE_NONE

#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "glfw3dll.lib")

#include <iostream>
#include <glfw3.h>

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

int main() {
	system_init();

	cout << "FIRST PARAMETER PROCESSING TEST" << endl;
	cout << "(I sure hope this works!!!)" << endl;
	dump_register_values();
	cout << "LOADING REG B -> D" << endl;
	execute(0b01000010);
	cout << "Executed." << endl;
	dump_register_values();

	return 0;
}