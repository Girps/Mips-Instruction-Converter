#include <iostream>
#include "FormatInstruction.h"
#include "RFormat.h"
#include "JFormat.h"
#include "IFormat.h"
#include <memory>
int main() 
{
		std::string digit;
		std::string bit; 
		std::string op; 
		std::unique_ptr<FormatInstruction> smrtPtr;
		int sent = 0;
		int value = 0; 

		do {

			std::cout << "\n\nEnter an 8 bit hexdecimal value to be converted into a 32-bit MIPS instruction terminate with 'q'\n";
			std::cin >> digit; 
			system("cls");
			// check if size is valid if not check if its a terminating char if not set -1 
			if (digit.size() == 8 || digit.size() == 10 || digit.size() == 32) 
			{
				bit = hextToBits(digit);
				op = getOp(bit.substr(0, 6));
				value = getFormat(op);	
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
				smrtPtr = std::make_unique<RFormat>(RFormat(digit, Binary));
				smrtPtr->printInstr();
				break;
			case(JForm):
				printf("J Format");
				smrtPtr = std::make_unique<JFormat>(JFormat(digit, Binary));
				smrtPtr->printInstr();
				break;
			case(IForm):
				printf("I Format");
				smrtPtr = std::make_unique<IFormat>(IFormat(digit, Binary));
				smrtPtr->printInstr();
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
		return 0; 
}