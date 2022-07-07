#include "IFormat.h"

/*
	File: IFormat.cpp defines IFormat function memebers
	and override abstract base memeber FormatInstruction
*/

/*Initalize base and derived members */
IFormat::IFormat(const std::string &digits, Base baseArg)
	:FormatInstruction(digits,baseArg)
{
	// Now initalize derived data members
	std::string bits = this->bitfields;
	// Initlalize bitfields of mips instruction
	rs = bitfields.substr(6, 5);
	rt = bitfields.substr(11, 5);
	immediate = bitfields.substr(16,16);
}

IFormat::~IFormat() {}

unKnownIInstruction::unKnownIInstruction(const char* msgArg) 
	:std::runtime_error(msgArg)
{ 
}

/* Print I Format instructions*/
void IFormat::printInstr() 
{
	
	std::cout << "\nNumber:" << this->digits << "\n" << "Bits: " << this->bitfields << "\n"
		<< this->op << "|" << this->rs << "|" << this->rt << "|" << this->immediate <<
		"\nI-format\n" << "op == " << this->op << "\n" << "rs == " << this->rs << "\n" <<
		"rt == " << this->rt << "\nimmediate == " << this->immediate << "\nTwos comp == " <<
		 isTwosComp(this->immediate) << "\nInstruction: " << getInstructions();
}

/*string returning function returns twos complement representation of a negative 
	binary digit*/
std::string IFormat::isTwosComp(const std::string& bits)
{
	// Check if 16 bit field is valid
	if (bits.size() != 16) 
	{
		throw unKnownBitField("Not a valid 16 bit immediate field");
	}
	else if(bits[0] == '0')
	{
		return "Does not apply!"; 
	}
	else
	{
		std::string temp = bits; 
		std::string twosComplementBits = numsToBits((std::stoi(temp, nullptr, 2) + 1));
		for (auto it = temp.begin(); it != temp.end(); ++it) 
		{
			(*it) = (*it == '0') ? '1' : '0'; 
		}
		return temp + "\n\t\t\t + 1\n\t     " + 
			twosComplementBits.substr(16,16) + "\n\t\t\t  " +
			std::to_string(convertImmediate());
	}
};

/*string returning functions returns decimal value of immediate bitfield
	depending on its addressing modes*/ 
int IFormat::convertImmediate( ) 
{
	int exp = 15; 
	int result = 0; 
	for (std::string::const_iterator it = immediate.begin();
			it != immediate.end(); ++it,--exp) 
	{
		if ( exp == 15 && *it == '1')
		{
			// - (2 ^ (15)) 
			result += (std::pow(2, exp) * -1);
		}
		else if (*it == '1')
		{
			// (2 ^ i) 
			result += std::pow(2, exp); 
		}
	}
	return result; 
}

/*string returning function converts bit members into string of instructions */ 
std::string IFormat::getInstructions() 
{
	std::string instr; 
	switch (std::stoi(this->op,nullptr,2)) 
	{
	case(4):
		instr += "\nimmediate == " + this->immediate; 
		instr += "\nsll 2 or multiply immediate by 4"; 
		instr += "\nbeq "; 
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "(PC + 4 + "; 
		instr += bitToHex(numsToBits((convertImmediate() * 4)));
		instr += ")\n"; 
		instr += "beq ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "label"; 
		break; 
	case(5):
		instr += "\nimmediate == " + this->immediate;
		instr += "\nsll 2 or multiply immediate by 4";
		instr += "\nbne ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "(PC + 4 + ";
		instr += bitToHex(numsToBits((convertImmediate() * 4)));
		instr += ")\n";
		instr += "bne ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "label";
		break;
	case(6):
		instr += "\nimmediate == " + this->immediate;
		instr += "\nsll 2 or multiply immediate by 4";
		instr += "\nblez ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += "(PC + 4 + ";
		instr += bitToHex(numsToBits((convertImmediate() * 4)));
		instr += ")\n";
		instr += "blez ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += "label";
		break;
	case(7):
		instr += "\nimmediate == " + this->immediate;
		instr += "\nsll 2 or multiply immediate by 4";
		instr += "\nbgtz ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += "(PC + 4 + ";
		instr += bitToHex(numsToBits((convertImmediate() * 4)));
		instr += ")\n";
		instr += "bgtz ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += "label";
		break; 
	case(8):
		instr += "addi ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break; 
	case(9):
		instr += "addiu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break; 
	case(10):
		instr += "slti ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break;
	case(11):
		instr += "sltiu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break;
	case(12):
		instr += "andi ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break;
	case(13):
		instr += "ori ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break;
	case(14):
		instr += "xori ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break;
	case(15):
		instr += "lui ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		break;
	case(32):
		instr += "lb ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "("; 
		instr += getRegisters(this->rs); 
		instr += ")"; 
		break;
	case(33):
		instr += "lh ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(34): 
		instr += "lwl "; 
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
			break; 
	case(35):
		instr += "lw ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(36):
		instr += "lbu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(37):
		instr += "lhu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(38):
		instr += "lwr ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(40):
		instr += "sb ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(41):
		instr += "sh ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(42):
		instr += "swl ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(43):
		instr += "sw ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(46): 
		instr += "swr ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(48):
		instr += "ll "; 
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(49):
		instr += "lwc1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(53):
		instr += "lwd1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(56):
		instr += "sc ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(57):
		instr += "swc1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(61):
		instr += "sdc1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate());
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	default: // throw error
		struct unKnownIInstruction("Unknown IFormat instruction");
		break; 
	}
	return instr; 
}


/*string returning function, converts an integer to a string of bits */
std::string IFormat::numsToBits(int nums) 
{
	std::string bits; 
	char msb = '0'; 
	int number = nums; 
	// int is postive or zero
	if (std::abs(number) > 0) 
	{
		for (;number != 0; number/=2 ) 
		{
			bits += (std::abs(number) % 2)? '1' : '0'; 
		}
	}
	else
	{
		bits += "0"; 
	}
	if (nums < 0) { bits += "1"; msb = '1'; }
	// sign extend and reverse 
	// get msb 

	// Sign extend to 32 bits
	for (; bits.size() != 32;)
	{
		bits.push_back(msb);
	}

	// reverse string
	int i = 0;
	int j = bits.size() - 1;
	for (; i < j; ++i)
	{
		char c = bits[j];
		bits[j--] = bits[i];
		bits[i] = c;
	}

	return bits; 
}