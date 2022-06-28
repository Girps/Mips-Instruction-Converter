#include "JFormat.h"

/*
	File: JFormat.cpp define JFormat type that will serve
	as an derived class of abstract base FormatInstruction class 
	class represents J type instructions and overrided virtual 
	function from base class. 
*/


/*JFormat constructor calls base constructor to initalize base memebers
	and initliazes its own members */ 
JFormat::JFormat(const std::string& digits, Base baseArg)
	:FormatInstruction(digits, baseArg)
{
	// Initalize J Format fields
	immediate = this->bitfields.substr(6,26); 
	this->instruction = getInstructions();
}

JFormat::~JFormat() {}

/*Void overried member function prints J Format instruction*/
void JFormat::printInstr()
{
	std::cout << "\nNumber:" << this->digits << "\n" << "Bits: " << this->bitfields << "\n"
		<< this->op << "|" << this->immediate << "\n" << "J-format\n" << "op == " << this->op << "\n"
		<< "Immediate == " << this->immediate << "\nDec Immediate == " << std::stoi(this->immediate, nullptr, 2)
		<< "\nMultiply by 4 or SLL by 2 immediate == " << (std::stoi(this->immediate, nullptr, 2) * 4)
		<< "\n" << "Instruction: " << this->instruction;
}

/*String returning overrided memberfunction checks memebers and returns instruction and its immediate*/
std::string JFormat::getInstructions()
{
	std::string instr; 
	// value of bit field
	int value = std::stoi(this->op,nullptr,2); 
	switch (value) 
	{		// jump 
	case(2):
		instr = "j "; 
		instr += getHex((stoi(this->immediate, nullptr, 2) * 4)); 
		break;
			// jump and link
	case(3):
		instr = "jal "; 
		// print the address(hex) and the generic label
		instr += getHex((stoi(this->immediate, nullptr, 2) * 4));
		instr += "\njal ";
		instr += "label"; 
		break; 
	default: 
		throw unknownJOp(); 
		break;
	}
	return instr; 
}

/*String returning member function converts a int decimal into hex string
	and "signed extends" to 32-bits */ 
std::string JFormat::getHex(int num)
{
	int numbers = 0;
	int digit = 0; 
	std::string temp; 
	for (numbers = num; numbers != 0; numbers/=16) 
	{
		digit = numbers % 16;
		switch(digit) 
		{
		case(0):
			temp.push_back('0');
			break; 
		case(1):
			temp.push_back('1');
			break; 
		case(2):
			temp.push_back('2');
			break; 
		case(3):
			temp.push_back('3');
			break; 
		case(4):
			temp.push_back('4');
			break; 
		case(5):
			temp.push_back('5');
			break; 
		case(6):
			temp.push_back('6');
			break; 
		case(7):
			temp.push_back('7');
			break;
		case(8):
			temp.push_back('8');
			break;
		case(9):
			temp.push_back('9');
			break;
		case(10):
			temp.push_back('A');
			break; 
		case(11):
			temp.push_back('B');
			break;
		case(12):
			temp.push_back('C');
			break; 
		case(13):
			temp.push_back('D');
			break; 
		case(14):
			temp.push_back('E');
			break;
		case(15):
			temp.push_back('F');
			break; 
		default: 
			throw unKnownBase(); 
			break; 
		}
	}
	temp.push_back('0');
	temp.push_back('0');
	temp.push_back('x');
	temp.push_back('0');

	// Now reverse a string
	int i = 0;
	int j = temp.size()- 1; 
	for (;i < j;++i) 
	{
		char c = temp[j]; 
		temp[j--] = temp[i];
		temp[i] = c; 
	}

	return temp; 
}
