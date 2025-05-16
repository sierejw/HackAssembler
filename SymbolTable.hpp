#pragma once
#include <map>
#include <string>

class SymbolTable
{
public:
	SymbolTable();
	void addEntry(std::string symbol, uint16_t address);
	bool contains(std::string symbol);
	uint16_t getAddress(std::string symbol);

private:
	std::map<std::string, uint16_t> symbolTable;
};

