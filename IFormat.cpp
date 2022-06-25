#include "IFormat.h"

/*Initalize base and derived members */
IFormat::IFormat(const std::string &digits, Base baseArg)
	:FormatInstruction(digits,baseArg)
{
	// Now initalize derived data members
	std::string bits = this->bitfields;
	// Initlalize bitfields of mips instruction
	rs = bitfields.substr(6, 5);
	rt = bitfields.substr(11, 5);
	immediate = bitfields.substr(15,16);
	instruction = getInstructions();
}

IFormat::~IFormat() {}

void IFormat::printInstr() 
{
}

std::string IFormat::getInstructions() 
{
	std::string instr; 
	switch (std::stoi(this->op,nullptr,2)) 
	{
	case(4):
		instr += "beq "; 
		instr += getRegisters(this->rs);
		instr += getRegisters(this->rt);
		break; 
	case(5):
		instr += "bne ";
		instr += getRegisters(this->rs);
		instr += getRegisters(this->rt);
		break;
	case(6):
		instr += "blez ";
		instr += getRegisters(this->rs);
		break;
	case(7):
		instr += "bgtz ";
		instr += getRegisters(this->rs);
		break; 
	case(8):
		instr += "addi ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break; 
	case(9):
		instr += "addiu ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break; 
	case(10):
		instr += "slti ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break;
	case(11):
		instr += "sltiu ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break;
	case(12):
		instr += "andi ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break;
	case(13):
		instr += "ori ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break;
	case(14):
		instr += "xori ";
		instr += getRegisters(this->rt);
		instr += getRegisters(this->rs);
		break;
	case(15):
		instr += "lui ";
		instr += getRegisters(this->rt);
		break;
	case(32):
		instr += "lb ";
		instr += getRegisters(this->rt);
		instr += "("; 
		instr += getRegisters(this->rs); 
		instr += ")"; 
		break;
	case(33):
		instr += "lh ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(34):
		instr += "lw ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(36):
		instr += "lbu ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(37):
		instr += "lhu ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(40):
		instr += "sb ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	case(41):
		instr += "sh ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break; 
	case(43):
		instr += "sw ";
		instr += getRegisters(this->rt);
		instr += "(";
		instr += getRegisters(this->rs);
		instr += ")";
		break;
	default: // throw error
		struct unKnownIInstr();
		break; 
	}
	return instr; 
}