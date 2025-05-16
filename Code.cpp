#include "Code.hpp"

// All results are shifted to fit 111accccccdddjjj binary format. c = computations, d = destinations, j = jumps. a is set in computations. all values are printed in binary eventually

// returns binary value according to Hack specification of the different locations shifted by 3 to fit ddd space in format above.
uint16_t Code::dest(Destinations destination)
{
	switch (destination)
	{
	case Destinations::m:
		return 1 << 3;

	case Destinations::d:
		return 2 << 3;

	case Destinations::dm:
		return 3 << 3;

	case Destinations::a:
		return 4 << 3;

	case Destinations::am:
		return 5 << 3;

	case Destinations::ad:
		return 6 << 3;

	case Destinations::adm:
		return 7 << 3;

	default:
		return 0;
	}
}

// returns binary value according to Hack specification of the different computations shifted by 6 to fit acccccc space in format above.
uint16_t Code::comp(Computations computations)
{
	switch (computations)
	{
	case Computations::one:
		return 63 << 6;

	case Computations::negOne:
		return 58 << 6;

	case Computations::d:
		return 12 << 6;

	case Computations::a:
		return 48 << 6;

	case Computations::notD:
		return 13 << 6;

	case Computations::notA:
		return 49 << 6;

	case Computations::negD:
		return 15 << 6;

	case Computations::negA:
		return 51 << 6;

	case Computations::dPlusOne:
		return 31 << 6;

	case Computations::aPlusOne:
		return 55 << 6;

	case Computations::dMinusOne:
		return 14 << 6;

	case Computations::aMinusOne:
		return 50 << 6;

	case Computations::dPlusA:
		return 2 << 6;

	case Computations::dMinusA:
		return 19 << 6;

	case Computations::aMinusD:
		return 7 << 6;

	case Computations::dAndA:
		return 0 << 6;

	case Computations::dOrA:
		return 21 << 6;

	case Computations::m:
		return 112 << 6;

	case Computations::notM:
		return 113 << 6;

	case Computations::negM:
		return 115 << 6;

	case Computations::mPlusOne:
		return 119 << 6;

	case Computations::mMinusOne:
		return 114 << 6;

	case Computations::dPlusM:
		return 66 << 6;

	case Computations::dMinusM:
		return 83 << 6;

	case Computations::mMinusD:
		return 71 << 6;

	case Computations::dAndM:
		return 64 << 6;

	case Computations::dOrM:
		return 85 << 6;

	default:
		return 42 << 6;
	}
}

// returns binary value according to Hack specification of the different jump locations to fit jjj space in format above.
uint16_t Code::jump(JumpCodes jumpCode)
{

	switch (jumpCode)
	{
	case JumpCodes::jgt:
		return 1;

	case JumpCodes::jeq:
		return 2;

	case JumpCodes::jge:
		return 3;

	case JumpCodes::jlt:
		return 4;

	case JumpCodes::jne:
		return 5;

	case JumpCodes::jle:
		return 6;

	case JumpCodes::jmp:
		return 7;

	default:
		return 0;
	}
}