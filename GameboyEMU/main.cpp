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

using namespace std;

int main() {
	memory_init();
	flags_init();

	return 0;
}