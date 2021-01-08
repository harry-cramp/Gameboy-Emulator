#define NUMBER_OF_CONST_OPCODES 17

#include "opcodes.h"

Opcode build_opcode(int code, int bytes, int cycle_count) {
	Opcode new_opcode;
	new_opcode.instruction_code = code;
	new_opcode.byte_size = bytes;
	new_opcode.cycles = cycle_count;

	return new_opcode;
}

Opcode instructions[NUMBER_OF_CONST_OPCODES];

void opcodes_init() {
	// initialise load instructions
	instructions[0] = build_opcode(LOAD_HL, 2, 3);
	instructions[1] = build_opcode(LOAD_A_BC, 1, 2);
	instructions[2] = build_opcode(LOAD_A_DE, 1, 2);
	instructions[3] = build_opcode(LOAD_BC, 1, 2);
	instructions[4] = build_opcode(LOAD_DE, 1, 2);
	instructions[5] = build_opcode(LOAD_A_ABS, 3, 4);
	instructions[6] = build_opcode(LOAD_ABS_A, 3, 4);
	instructions[7] = build_opcode(LOADH_A_C, 1, 2);
	instructions[8] = build_opcode(LOADH_C_A, 1, 2);
	instructions[9] = build_opcode(LOADH_A_ABS, 2, 3);
	instructions[10] = build_opcode(LOADH_ABS_A, 2, 3);
	instructions[11] = build_opcode(LOAD_A_ABSHL_DEC, 1, 2);
	instructions[12] = build_opcode(LOAD_ABSHL_A_DEC, 1, 2);
	instructions[13] = build_opcode(LOAD_A_ABSHL_INC, 1, 2);
	instructions[14] = build_opcode(LOAD_ABSHL_A_INC, 1, 2);
	instructions[15] = build_opcode(LOAD_ABS_SP, 3, 5);
	instructions[16] = build_opcode(LOAD_SP_HL, 1, 2);
}