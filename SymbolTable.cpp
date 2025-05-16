#include "SymbolTable.hpp"

// Sets default symbols in symbol table according to Hack specification
SymbolTable::SymbolTable():
	symbolTable
	{
		{"R0", 0},
		{"R1", 1},
		{"R2", 2},
		{"R3", 3},
		{"R4", 4},
		{"R5", 5},
		{"R6", 6},
		{"R7", 7},
		{"R8", 8},
		{"R9", 9},
		{"R10", 10},
		{"R11", 11},
		{"R12", 12},
		{"R13", 13},
		{"R14", 14},
		{"R15", 15},
		{"SCREEN", 16384},
		{"KBD", 24576}
	}
{
}

// Adds entry into symbol table
void SymbolTable::addEntry(std::string symbol, uint16_t address)
{
	symbolTable.insert({ symbol, address });
}

// Checks if symbol is already in symbol table
bool SymbolTable::contains(std::string symbol)
{
	return symbolTable.contains(symbol);
}

// returns address associated with symbol in symbol table
uint16_t SymbolTable::getAddress(std::string symbol)
{
	return symbolTable.at(symbol);
}