#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

#include "parameter_processor.h"

using namespace std;

int parse_bit(char bit_char) {
	if (bit_char == '0')
		return 0;
	else if (bit_char == '1')
		return 1;
	else
		return -1;
}

int parse_int(string str) {
	stringstream ss(str);
	int num;
	ss >> num;
	return num;
}

int* extract_parameters(int opcode, int x_index, int y_index) {
	int* parameters = (int*)malloc(sizeof(int) * 2);
	
	// extract x parameter
	int x_binary_index = 0;
	x_binary_index += pow(2, OPCODE_LENGTH - x_index - 1);
	x_binary_index += pow(2, OPCODE_LENGTH - x_index - 2);
	x_binary_index += pow(2, OPCODE_LENGTH - x_index - 3);

	int shift_factor = 0;
	if (x_index < 5)
		shift_factor = OPCODE_LENGTH - x_index - 3;

	parameters[0] = (opcode & x_binary_index) >> shift_factor;

	if (y_index != -1) {
		// extract y parameter
		int y_binary_index = 0;
		y_binary_index += pow(2, OPCODE_LENGTH - y_index - 1);
		y_binary_index += pow(2, OPCODE_LENGTH - y_index - 2);
		y_binary_index += pow(2, OPCODE_LENGTH - y_index - 3);

		shift_factor = 0;
		if(y_index < 5)
			shift_factor = OPCODE_LENGTH - y_index - 3;

		parameters[1] = (opcode & y_binary_index) >> shift_factor;
	}

	return parameters;
}

int* get_parameters_if_match(int opcode, const char opcode_template[]) {
	// detect if opcode fits specified template
	int x_parameter_index = -1;
	int y_parameter_index = -1;
	for (int i = 0; i < OPCODE_LENGTH; i++) {
		int true_index = OPCODE_LENGTH - i - 1;
		int high_bit = (opcode & (int)pow(2, true_index)) >> true_index;

		if (parse_bit(opcode_template[i]) == -1) {
			if (x_parameter_index == -1)
				x_parameter_index = i;
			else
				y_parameter_index = i;
			i += 2;
			continue;
		}

		if (parse_bit(opcode_template[i]) != high_bit)
			return (int*)-1;
	}

	return extract_parameters(opcode, x_parameter_index, y_parameter_index);
}