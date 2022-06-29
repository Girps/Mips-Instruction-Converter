#include <iostream>
#include "FormatInstruction.h"
#include "RFormat.h"
#include "JFormat.h"
#include "IFormat.h"
#include "FRFormat.h"
#include <memory>
/*
	Author: Jesse Jimenez
	Date: 6/27/2022
	Purpose: Enter a 8 digit hexadecimal value or 32-bit binary sequence to be converted into a
	32-bit MIPs instruction. 
*/

int main() 
{
		std::string digit;
		std::string bit; 
		std::string op; 
		std::unique_ptr<FormatInstruction> smrtPtr;
		int sent = 0;
		int value = 0; 
		Base baseNumber = Hex; 

		try {
			do {

				std::cout << "\n\nEnter a 8 bit hexdecimal value or 32-bit binary number to be converted into a 32-bit MIPS instruction\n" <<
					"terminate program with 'q'\n";
				std::cin >> digit;
				system("cls");
				// check if size is valid if not check if its a terminating char if not set -1 
				if (digit.size() == 8 || digit.size() == 10)
				{
					bit = hextToBits(digit);
					op = bit.substr(0, 6);
					value = getFormat(op);
				}
				else if (digit.size() == 32)
				{
					op = digit.substr(0, 6);
					value = getFormat(op);
					baseNumber = Binary;
				}
				else if (digit[0] == 'q' && digit.size() == 1)
				{
					value = 'q';
				}
				else
				{
					value = -1;
				}

				// Check cases on the format 
				switch (value)
				{
				case(RForm):
					smrtPtr = std::make_unique<RFormat>(RFormat(digit, baseNumber));
					smrtPtr->printInstr();
					break;
				case(JForm):
					printf("J Format");
					smrtPtr = std::make_unique<JFormat>(JFormat(digit, baseNumber));
					smrtPtr->printInstr();
					break;
				case(IForm):
					printf("I Format");
					smrtPtr = std::make_unique<IFormat>(IFormat(digit, baseNumber));
					smrtPtr->printInstr();
					break;
				case(FRForm):
					printf("FR Fromat");
					smrtPtr = std::make_unique<FRFormat>(FRFormat(digit, baseNumber));
					smrtPtr->printInstr();
					break; 
					break; 
				case((int)'q'):
					sent = 1;
					std::cout << "Program terminated\n";
					break;
				default:
					std::cout << "***ERROR input a valid 8 bit hex instruction ***\n";
					break;
				}

				// reset smrt pointer 
				smrtPtr.reset();
				// Clear buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			} while (sent == 0);
		}
		catch (...) 
		{
			std::cout << "Exception caught!\n"; 
			return 1; 
		}
		return 0; 
}