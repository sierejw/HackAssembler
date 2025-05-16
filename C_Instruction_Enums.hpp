#pragma once
enum class CommandType
{
	a_Command,
	c_Command,
	l_Command,
	skip
};

enum class Destinations
{
	null,
	m,
	d,
	dm,
	a,
	am,
	ad,
	adm
};

enum class Computations
{
	zero,
	one,
	negOne,
	d,
	a,
	notD,
	notA,
	negD,
	negA,
	dPlusOne,
	aPlusOne,
	dMinusOne,
	aMinusOne,
	dPlusA,
	dMinusA,
	aMinusD,
	dAndA,
	dOrA,
	m,
	notM,
	negM,
	mPlusOne,
	mMinusOne,
	dPlusM,
	dMinusM,
	mMinusD,
	dAndM,
	dOrM
};

enum class JumpCodes
{
	null,
	jgt,
	jeq,
	jge,
	jlt,
	jne,
	jle,
	jmp
};