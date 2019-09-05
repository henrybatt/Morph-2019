#pragma once
#include "bno055.h"
#include "bno055.cpp"

s8 bno055_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
s8 bno055_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
void bno055_delay_ms(u32 ms);
