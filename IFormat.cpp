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
		"rt == " << this->rt << "\nimmediate == " << this->immediate << "\n" <<
		"Instruction: " << getInstructions();

}

/*string returning functions returns decimal value of immediate bitfield
	depending on its addressing modes*/ 
int IFormat::convertImmediate(AddressMode arg) 
{
	int exp = 15; 
	int result = 0; 
	for (std::string::const_iterator it = immediate.begin();
			it != immediate.end(); ++it,--exp) 
	{
		if (*it == '1' && exp == 15)
		{
			// - (2 ^ (15)) 
			result += (arg != RelativeAddress) ? (std::pow(2, exp) * -1) : (std::pow(2, exp)); 
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
		instr += "beq "; 
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "(PC + 4 + "; 
		instr += getHex((convertImmediate(RelativeAddress) * 4));
		instr += ")\n"; 
		instr += "beq ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "label"; 
		break; 
	case(5):
		instr += "bne ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "(PC + 4 + ";
		instr += getHex((convertImmediate(RelativeAddress) * 4));
		instr += ")\n";
		instr += "beq ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "label";
		break;
	case(6):
		instr += "blez ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "(PC + 4 + ";
		instr += getHex((convertImmediate(RelativeAddress) * 4));
		instr += ")\n";
		instr += "beq ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "label";
		break;
	case(7):
		instr += "bgtz ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "(PC + 4 + ";
		instr += getHex((convertImmediate(RelativeAddress) * 4));
		instr += ")\n";
		instr += "beq ";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += "label";
		break; 
	case(8):
		instr += "addi ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break; 
	case(9):
		instr += "addiu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break; 
	case(10):
		instr += "slti ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break;
	case(11):
		instr += "sltiu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break;
	case(12):
		instr += "andi ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break;
	case(13):
		instr += "ori ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break;
	case(14):
		instr += "xori ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += getRegisters(this->rs);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break;
	case(15):
		instr += "lui ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(ImmediateAddressing));
		break;
	case(32):
		instr += "lb ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "("; 
		instr += getRegisters(this->rs); 
		instr += ")"; 
		break;
	case(33):
		instr += "lh ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(34): 
		instr += "lwl "; 
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
			break; 
	case(35):
		instr += "lw ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(36):
		instr += "lbu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(37):
		instr += "lhu ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(38):
		instr += "lwr ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(40):
		instr += "sb ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(41):
		instr += "sh ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(42):
		instr += "swl ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(43):
		instr += "sw ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(46): 
		instr += "swr ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(48):
		instr += "ll "; 
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(49):
		instr += "lwc1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(53):
		instr += "lwd1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(56):
		instr += "sc ";
		instr += getRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(57):
		instr += "swc1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(61):
		instr += "sdc1 ";
		instr += getFPRegisters(this->rt);
		instr += ",";
		instr += std::to_string(convertImmediate(BaseAddressing));
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

/* string returing function converts decimal into a string of hex to be returned*/ 
std::string IFormat::getHex(int num)
{
	int numbers = 0;
	int digit = 0;
	std::string temp;
	for (numbers = num; numbers != 0; numbers /= 16)
	{
		digit = numbers % 16;
		switch (digit)
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
			throw unKnownBase("Failed to convert decimal to hex!");
			break;
		}
	}

	// Extend to 8 bit
	for (int offset = 8 - temp.size(); offset >= temp.size();) 
	{
		temp.push_back('0');
	}
	// Push prefix 
	temp.push_back('x');
	temp.push_back('0');

	// Now reverse a string
	int i = 0;
	int j = temp.size() - 1;
	for (; i < j; ++i)
	{
		char c = temp[j];
		temp[j--] = temp[i];
		temp[i] = c;
	}

	return temp;
}