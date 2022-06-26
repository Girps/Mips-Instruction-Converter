#include <iostream>
#include "FormatInstruction.h"
#include "RFormat.h"
#include "JFormat.h"
#include "IFormat.h"
#include <memory>
int main() 
{
		std::string digit;
		std::cout << "Enter an 8 bit hexdecimal value to be converted into a MIPS instruction\n";
		std::cin >> digit;
		std::string bit = hextToBits(digit);
		std::string op = getOp(bit.substr(0, 6));
		int value = getFormat(op);
		std::unique_ptr<FormatInstruction> smrtPtr;
		

		switch (value)
		{
		case(RForm):
			smrtPtr = std::make_unique<RFormat>(RFormat(digit, Hex));
			smrtPtr->printInstr();
			break;
		case(JForm):
			printf("J Format");
			smrtPtr = std::make_unique<JFormat>(JFormat(digit, Hex));
			smrtPtr->printInstr();
			break;
		case(IForm):
			printf("I Format");
			smrtPtr = std::make_unique<IFormat>(IFormat(digit, Hex)); 
			smrtPtr->printInstr(); 
			break;
		}
		return 0; 
}