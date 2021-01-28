#pragma once

// all of the constant opcodes used by the Gameboy's SM83 CPU

// load instructions
const int LOAD_HL = 0x36;
const int LOAD_A_BC = 0x0A;
const int LOAD_A_DE = 0x1A;
const int LOAD_BC = 0x02;
const int LOAD_DE = 0x12;
const int LOAD_A_ABS = 0xFA;
const int LOAD_ABS_A = 0xEA;
const int LOADH_A_C = 0xF2;
const int LOADH_C_A = 0xE2;
const int LOADH_A_ABS = 0xF0;
const int LOADH_ABS_A = 0xE0;
const int LOAD_A_ABSHL_DEC = 0x3A;
const int LOAD_ABSHL_A_DEC = 0x32;
const int LOAD_A_ABSHL_INC = 0x2A;
const int LOAD_ABSHL_A_INC = 0x22;
const int LOAD_ABS_SP = 0x08;
const int LOAD_SP_HL = 0xF9;

// jump instructions
const int JUMP_ABS_OP = 0xC3;
const int JUMP_HL = 0xE9;
const int JUMP_REL = 0x18;

// flag-wise instructions
const int FLIP_CARRY = 0x3F;
const int SET_CARRY = 0x37;
const int FLIP_ACC = 0x2F;