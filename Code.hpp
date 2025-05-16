#pragma once
#include <cstdint>
#include "C_Instruction_Enums.hpp"

class Code
{
public:
	uint16_t dest(Destinations destination);
	uint16_t comp(Computations computation);
	uint16_t jump(JumpCodes jumpCode);
};