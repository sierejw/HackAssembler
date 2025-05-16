// HackAssembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <fstream>
#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolTable.hpp"

    int main(int argc, char* argv[])
    {
        CommandType commandType{};
        Code translator{};
        SymbolTable table{};

        //Values for first Pass
        Parser parser{ argv[1] };
        uint16_t counter{ 0 };

        // First Pass: Checks for all labels in assembly and adds them and their values to symbol table
        while (parser.hasMoreCommands())
        {   
            parser.advance();
            commandType = parser.getCommandType();

            if (commandType == CommandType::l_Command)
            {
                table.addEntry(parser.symbol(), counter);
            } 
            
            // if the current command is c or a type, add to line counter. All other lines will not contribute to output directly
            if (commandType == CommandType::a_Command || commandType == CommandType::c_Command)
            {
                ++counter;
            }
        }

        // reset file for second pass
        parser.reset();

        //Values for C instructions
        uint16_t cDefault{ 57344 };
        Destinations destination{};
        Computations computation{};
        JumpCodes jump{};
        uint16_t destVal{ 0 };
        uint16_t compVal{ 0 };
        uint16_t jumpVal{ 0 };
        
        //Values for A instructions
        uint16_t tableAddress{ 16 };
        std::string aInstrucLoc{};

        //Values for output to .hack file
        uint16_t output{ 0 };
        std::string outputString{};
        std::ofstream binaryFile{ "Prog.hack" };
        
        
        // Second Pass through file
        while (parser.hasMoreCommands())
        {   
            parser.advance();
            commandType = parser.getCommandType();

            switch (commandType)
            {
            case CommandType::c_Command:
                //Parse current line's destination, computation, and jump location
                destination = parser.dest();
                computation = parser.comp();
                jump = parser.jump();

                // Translate those values into their binary forms
                destVal = translator.dest(destination);
                compVal = translator.comp(computation);
                jumpVal = translator.jump(jump);
                
                //Or them together with leading default value of a c instruction
                output = static_cast<uint16_t>(cDefault | destVal | compVal | jumpVal);
                
                //Convert back to string and write to .hack file
                outputString = std::bitset<16>(output).to_string();
                binaryFile << outputString << std::endl;
                break;

            case CommandType::a_Command:
                aInstrucLoc = parser.symbol();

                //Check if the symbol is a number
                if (std::find_if(aInstrucLoc.begin(), aInstrucLoc.end(), [](char c) { return !std::isdigit(c); }) == aInstrucLoc.end())
                {
                    output = static_cast<uint16_t>(std::stoi(aInstrucLoc));
                }
                else
                {
                    if (!table.contains(aInstrucLoc))
                    {
                        table.addEntry(aInstrucLoc, tableAddress++);
                    }
                    
                    output = table.getAddress(aInstrucLoc);
                }
                
                //Convert binary to string and write to .hack file
                outputString = std::bitset<16>(output).to_string();
                binaryFile << outputString << std::endl;
                break;
            default:
                break;
            }
        }

        binaryFile.close();
        return 0;
    }