#pragma once
#include <string>
#include <fstream>
#include "C_Instruction_Enums.hpp"


class Parser
{
public:
	Parser(std::string fileName); //Opens file, gets ready to parse it
	bool hasMoreCommands();
	void advance();
	CommandType getCommandType();
	Destinations dest();
	Computations comp();
	JumpCodes jump();
	std::string symbol();
	void reset();

private:
	std::ifstream asmFile;
	std::string currInstruction;
	
};

