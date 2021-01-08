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