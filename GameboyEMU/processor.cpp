#include <iostream>

#include "opcodes.h"
#include "memory.h"
#include "register.h"
#include "processor.h"

using namespace std;

Register accumulator;
Register bc_register;
Register de_register;
Register hl_register;
Register temp_register;
Register stack_pointer;
Register program_counter;

// print out register contents for testing purposes
void dump_register_values() {
	cout << "ACCUMULATOR: " << accumulator.value << endl;
	cout << "BC: " << bc_register.value << endl;
	cout << "DE: " << de_register.value << endl;
	cout << "HL: " << hl_register.value << endl;
	cout << "SP: " << stack_pointer.value << endl;
	cout << "PC: " << program_counter.value << endl;
}

void processor_init() {
	register_init(&accumulator, REGISTER_SIZE_8_BIT, 69);
	register_init(&bc_register, REGISTER_SIZE_16_BIT, 0);
	register_init(&de_register, REGISTER_SIZE_16_BIT, 0);
	register_init(&hl_register, REGISTER_SIZE_16_BIT, 0);
	register_init(&temp_register, REGISTER_SIZE_16_BIT, 0);
	register_init(&stack_pointer, REGISTER_SIZE_16_BIT, 0);
	register_init(&program_counter, REGISTER_SIZE_16_BIT, 0);
}

void load_from_abs_address_to_register(struct Register source_reg, struct Register* receiver_reg, bool high) {
	// data = read(source register)
	int address = (high) ? generate_full_address(source_reg.value, 0xFF) : source_reg.value;
	int data = get_data(address);
	// receiver register = data
	set_register_value(receiver_reg, data);
}

void load_from_register_to_abs_address(struct Register data_source_reg, struct Register address_source_reg, bool high) {
	// data = data source register
	int data = data_source_reg.value;
	// address = address source register
	int address = (high) ? generate_full_address(address_source_reg.value, 0xFF) : address_source_reg.value;
	set_data(address, data);
}

int generate_full_address(int lsb, int msb) {
	int full_address = (msb << 8) + lsb;
	cout << "GENERATED FULL ADDRESS: " << full_address << endl;
	return (msb << 8) + lsb;
}

// get PC value and increment
int get_program_counter_inc() {
	int program_counter_value = program_counter.value;
	program_counter.value = program_counter.value + 1;
	return program_counter_value;
}

void execute(int opcode) {
	switch (opcode) {
		// load immediate data n -> data at address HL
		case LOAD_HL: {
			// n = read(PC++)
			int n = get_data(program_counter.value);
			set_register_value(&program_counter, program_counter.value + 1);
			// data at address HL = n
			set_data(hl_register.value, n);
			break;
		}

		// load data from abs address in BC -> A
		case LOAD_A_BC: {
			load_from_abs_address_to_register(bc_register, &accumulator, false);
			break;
		}

		case LOAD_A_DE: {
			load_from_abs_address_to_register(de_register, &accumulator, false);
			break;
		}

		case LOAD_BC: {
			load_from_register_to_abs_address(accumulator, bc_register, false);
			break;
		}

		case LOAD_DE: {
			load_from_register_to_abs_address(accumulator, de_register, false);
			break;
		}

		case LOAD_A_ABS: {
			int lsb_parameter = get_data(get_program_counter_inc());
			cout << "LSB: " << lsb_parameter << endl;
			int msb_parameter = get_data(get_program_counter_inc());
			cout << "MSB: " << msb_parameter << endl;
			temp_register.value = generate_full_address(lsb_parameter, msb_parameter);
			load_from_abs_address_to_register(temp_register, &accumulator, false);
			break;
		}

		case LOAD_ABS_A: {
			int lsb_parameter = get_data(get_program_counter_inc());
			int msb_parameter = get_data(get_program_counter_inc());
			temp_register.value = generate_full_address(lsb_parameter, msb_parameter);
			load_from_register_to_abs_address(accumulator, temp_register, false);
			break;
		}

		case LOADH_A_C: {
			load_from_abs_address_to_register(bc_register, &accumulator, true);
			break;
		}

		default:
			// process non-constant opcodes
			break;
	}
}