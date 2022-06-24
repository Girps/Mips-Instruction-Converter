#include <iostream>
#include "FormatInstruction.h"
#include "RFormat.h"
#include <memory>
int main() 
{
	std::string digit; 
	std::cout << "Enter an 8 bit hexdecimal value to be converted into a MIPS instruction\n"; 
	std::cin >> digit; 
	std::string bit = hextToBits(digit);
	std::string op = getOp(bit.substr(0,6));
	int value = getFormat(op); 
	FormatInstruction* ptr = nullptr; 
	switch (value)
	{
	case(RForm): 
		ptr = new RFormat(digit,Hex);
		ptr->printInstr(); 
		break; 
	case(JForm):
		printf("J Format");
		break;
	case(IForm):
		printf("I Format");
		break; 
	}
	delete ptr;
	return 0; 
}