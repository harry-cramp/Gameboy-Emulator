#pragma once

#include <string>

const int OPCODE_LENGTH = 8;

// Some instructions on the SM83 CPU have parameters embedded in the opcodes themselves.
// These constants are templates for those instructions and are defined as such:
//
// 01XXXYYY		-		Load data from register XXX to register YYY

const char TEMPLATE_LOAD_REGISTER_TO_REGISTER[] = "01XXXYYY";
const char TEMPLATE_LOAD_IMMEDIATE_TO_REGISTER[] = "00XXX110";
const char TEMPLATE_LOAD_HL_ABSOLUTE_TO_REGISTER[] = "01XXX110";
const char TEMPLATE_LOAD_REGISTER_TO_HL_ABSOLUTE[] = "01110XXX";
const char TEMPLATE_LOAD_IMMEDIATE_TO_REGISTER_16[] = "00XX0001";

int* get_parameters_if_match(int, const char[]);