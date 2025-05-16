#include "Parser.hpp"
#include <iostream>

// Creates parser and opens file to be parsed
Parser::Parser(std::string fileName):
	asmFile { fileName }
{
}

// Checks if there's more lines to read
bool Parser::hasMoreCommands()
{
	return !(asmFile.peek() == std::ifstream::traits_type::eof());
}

// Reads next line
void Parser::advance()
{
	std::getline(asmFile >> std::ws, currInstruction);
	currInstruction.erase(std::remove_if(currInstruction.begin(), currInstruction.end(), [](unsigned char c) { return std::isspace(c); }));
}

// Returns type of command on current line
CommandType Parser::getCommandType()
{	
	if (currInstruction[0] != '/' && !currInstruction.empty())
	{	
		switch (currInstruction[0])
		{
		case '@':
			return CommandType::a_Command;

		case '(':
			return CommandType::l_Command;

		default:
			return CommandType::c_Command;
		}
	}
	//if no matches, skip the line.
	return CommandType::skip;
}

// returns destination location from current line
Destinations Parser::dest()
{
	if (currInstruction.find("=") != std::string::npos) 
	{
		if (currInstruction[0] == 'A')
		{
			if (currInstruction[1] == 'D')
			{
				if (currInstruction[3] == 'M')
				{
					return Destinations::adm;
				}
				return Destinations::ad;
			}

			if (currInstruction[1] == 'M')
			{
				if (currInstruction[2] == 'D')
				{
					return Destinations::adm;
				}
				return Destinations::am;
			}

			return Destinations::a;
		}

		if (currInstruction[0] == 'D')
		{
			if (currInstruction[1] == 'M')
			{

				return Destinations::dm;
			}
			return Destinations::d;
		}

		if (currInstruction[0] == 'M')
		{
			if (currInstruction[1] == 'D')
			{

				return Destinations::dm;
			}
			return Destinations::m;
		}
	}
	return Destinations::null;
}

// returns computation from current line
Computations Parser::comp()
{
	std::size_t startPos = currInstruction.find("=");
	std::size_t endPos = currInstruction.find(";") ;
	++startPos;

	if (startPos == std::string::npos)
	{
		startPos = 0;
	}

	if (endPos == std::string::npos)
	{
		endPos = currInstruction.size();
	}
	
	std::size_t difference = endPos - startPos;
	std::string computation = currInstruction.substr(startPos, difference);

	if (computation == "0")
	{
		return Computations::zero;
	}

	if (computation == "1")
	{
		return Computations::one;
	}

	if (computation == "-1")
	{
		return Computations::negOne;
	}

	if (computation == "D")
	{
		return Computations::d;
	}

	if (computation == "A")
	{
		return Computations::a;
	}
	
	if (computation == "!D")
	{
		return Computations::notD;
	}

	if (computation == "!A")
	{
		return Computations::notA;
	}

	if (computation == "-D")
	{
		return Computations::negD;
	}

	if (computation == "-A")
	{
		return Computations::negA;
	}

	if (computation == "D+1")
	{
		return Computations::dPlusOne;
	}

	if (computation == "A+1")
	{
		return Computations::aPlusOne;
	}

	if (computation == "D-1")
	{
		return Computations::dMinusOne;
	}

	if (computation == "A-1")
	{
		return Computations::aMinusOne;
	}

	if (computation == "D+A")
	{
		return Computations::dPlusA;
	}

	if (computation == "D-A")
	{
		return Computations::dMinusA;
	}

	if (computation == "A-D")
	{
		return Computations::aMinusD;
	}

	if (computation == "D&A")
	{
		return Computations::dAndA;
	}

	if (computation == "D|A")
	{
		return Computations::dOrA;
	}

	if (computation == "M")
	{
		return Computations::m;
	}

	if (computation == "!M")
	{
		return Computations::notM;
	}

	if (computation == "-M")
	{
		return Computations::negM;
	}

	if (computation == "M+1")
	{
		return Computations::mPlusOne;
	}

	if (computation == "M-1")
	{
		return Computations::mMinusOne;
	}

	if (computation == "D+M")
	{
		return Computations::dPlusM;
	}

	if (computation == "D-M")
	{
		return Computations::dMinusM;
	}

	if (computation == "M-D")
	{
		return Computations::mMinusD;
	}

	if (computation == "D&M")
	{
		return Computations::dAndM;
	}

	if (computation == "D|M")
	{
		return Computations::dOrM;
	}

	return Computations::zero;
}

// returns jump code from current line
JumpCodes Parser::jump()
{
	std::size_t startPos = currInstruction.find(';');

	if (startPos == std::string::npos)
	{
		return JumpCodes::null;
	}

	std::string jumpCode = currInstruction.substr(startPos+1);

	if (!(std::strcmp(jumpCode.c_str(), "JGT")))
	{
		return JumpCodes::jgt;
	}

	if (!(std::strcmp(jumpCode.c_str(), "JEQ")))
	{
		return JumpCodes::jeq;
	}

	if (!(std::strcmp(jumpCode.c_str(), "JGE")))
	{
		return JumpCodes::jge;
	}

	if (!(std::strcmp(jumpCode.c_str(), "JLT")))
	{
		return JumpCodes::jlt;
	}

	if (!(std::strcmp(jumpCode.c_str(), "JNE")))
	{
		return JumpCodes::jne;
	}

	if (!(std::strcmp(jumpCode.c_str(), "JLE")))
	{
		return JumpCodes::jle;
	}

	if (!(std::strcmp(jumpCode.c_str(), "JMP")))
	{
		return JumpCodes::jmp;
	}

	return JumpCodes::null;
}

// returns numeric or word symbol with current l or a command
std::string Parser::symbol()
{ 
	if (currInstruction[0] == '@')
	{
		return currInstruction.substr(1);
	}
	else 
	{
		size_t length = currInstruction.size() - 2;
		return currInstruction.substr(1, length);
	}
	
}

// resets assembly file for second pass through
void Parser::reset()
{
	asmFile.clear();
	asmFile.seekg(0, asmFile.beg);
} 