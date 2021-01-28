#pragma once

const int ZERO_FLAG = 3;
const int SUBTRACT_FLAG = 2;
const int HALF_CARRY_FLAG = 1;
const int CARRY_FLAG = 0;
const int FLAG_COUNT = 4;

void flags_init();
void clear_flag(int flag);
void set_flag(int flag);
void flip_flag(int flag);
bool flag_set(int flag);