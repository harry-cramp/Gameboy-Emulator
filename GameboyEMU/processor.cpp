#include <iostream>

#include "opcodes.h"
#include "memory.h"
#include "register.h"
#include "processor.h"
#include "parameter_processor.h"

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
	register_init(&accumulator, REGISTER_SIZE_8_BIT, 0);
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

void load_register_to_register(struct Register source_reg, int source_size, struct Register* receiver_reg, int receiver_size) {
	int source_value = 0;
	switch (source_size) {
		case REGISTER_FULL:
			source_value = source_reg.value;
			break;

		case REGISTER_LOW:
			source_value = source_reg.value & 0x00FF;
			break;

		case REGISTER_HIGH:
			source_value = (source_reg.value & 0xFF00) >> 8;
			break;
	}

	switch (receiver_size) {
		case REGISTER_FULL:
			receiver_reg->value = source_reg.value;
			break;
		case REGISTER_LOW:
			receiver_reg->value = (receiver_reg->value & 0xFF00) + source_reg.value;
			break;
		case REGISTER_HIGH:
			receiver_reg->value = (receiver_reg->value & 0x00FF) + (source_reg.value << 8);
			break;
	}
}

int generate_full_address(int lsb, int msb) {
	return (msb << 8) + lsb;
}

// get PC value and increment
int get_program_counter_inc() {
	int program_counter_value = program_counter.value;
	increment_register(&program_counter);
	return program_counter_value;
}

int register_is_upper(int register_id) {
	switch (register_id) {
		case REGISTER_ACCUMULATOR:
			return REGISTER_FULL;
		default:
			return register_id % 2;
	}
}

Register* get_register_from_id(int register_id) {
	if (register_id == 0b000 || register_id == 0b001)
		return &bc_register;
	else if (register_id == 0b010 || register_id == 0b011)
		return &de_register;
	else if (register_id == 0b100 || register_id == 0b101 || register_id == 0b110)
		return &hl_register;
	else
		return &accumulator;
}

void process_parameter_instructions(int opcode) {
	int* parameters;
	if (parameters = get_parameters_if_match(opcode, TEMPLATE_LOAD_REGISTER_TO_REGISTER)) {
		cout << "MATCH FOUND: LOAD REGISTER TO REGISTER" << endl;
		// get if parameters high
		// get reg from parameters
		// load from source to destination
	}
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

		// load data from abs address in A -> BC
		case LOAD_BC: {
			load_from_register_to_abs_address(accumulator, bc_register, false);
			break;
		}

		case LOAD_DE: {
			load_from_register_to_abs_address(accumulator, de_register, false);
			break;
		}

		// load data from abs address as parameter -> A
		case LOAD_A_ABS: {
			int lsb_parameter = get_data(get_program_counter_inc());
			int msb_parameter = get_data(get_program_counter_inc());
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

		// load from abs address in C to A using high addressing (prefix 0xFF onto specified address)
		case LOADH_A_C: {
			temp_register.value = get_lower_register_value(bc_register);
			load_from_abs_address_to_register(temp_register, &accumulator, true);
			break;
		}

		case LOADH_C_A: {
			temp_register.value = get_lower_register_value(bc_register);
			load_from_register_to_abs_address(accumulator, temp_register, true);
			break;
		}

		// load from abs address in memory (PC + 1) to A using high addressing
		case LOADH_A_ABS: {
			temp_register.value = get_data(get_program_counter_inc());
			load_from_abs_address_to_register(temp_register, &accumulator, true);
			break;
		}

		case LOADH_ABS_A: {
			temp_register.value = get_data(get_program_counter_inc());
			load_from_register_to_abs_address(accumulator, temp_register, true);
			break;
		}

		// load between memory and HL register and decrement/increment HL
		case LOAD_A_ABSHL_DEC: {
			load_from_abs_address_to_register(hl_register, &accumulator, false);
			decrement_register(&hl_register);
			break;
		}

		case LOAD_ABSHL_A_DEC: {
			load_from_register_to_abs_address(accumulator, hl_register, false);
			decrement_register(&hl_register);
			break;
		}

		case LOAD_A_ABSHL_INC: {
			load_from_abs_address_to_register(hl_register, &accumulator, false);
			increment_register(&hl_register);
			break;
		}

		case LOAD_ABSHL_A_INC: {
			load_from_register_to_abs_address(accumulator, hl_register, false);
			increment_register(&hl_register);
			break;
		}

		case LOAD_ABS_SP: {
			int lsb_parameter = get_data(get_program_counter_inc());
			int msb_parameter = get_data(get_program_counter_inc());
			temp_register.value = generate_full_address(lsb_parameter, msb_parameter);
			load_from_register_to_abs_address(stack_pointer, temp_register, false);
			break;
		}

		case LOAD_SP_HL: {
			set_register_value(&stack_pointer, hl_register.value);
			break;
		}

		default:
			// process non-constant opcodes
			cout << "NON-CONSTANT OPCODE ENCOUNTERED" << endl;
			process_parameter_instructions(opcode);
			break;
	}
}