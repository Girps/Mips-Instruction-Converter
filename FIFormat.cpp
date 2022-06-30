#include "FIFormat.h"


/*Constructor takes in string of values of base BaseArg initializes
	data fields of FIFormat*/
FIFormat::FIFormat(const std::string &nums, Base baseArg)
	:IFormat(nums, baseArg), fmt{ rt }, ft{rs}
{
}

FIFormat::~FIFormat() {}

/* string returning function converts bit fields into 
	Floating point I instruction*/
std::string FIFormat::getInstructions()
{
	int ftInt = std::stoi(fmt,nullptr,2);
	std::string instr; 
	switch (ftInt) 
	{
	case(1):
		instr = "bclt ";
		instr += "(PC + 4 + ";
		instr += getHex((convertImmediate(RelativeAddress) * 4));
		instr += ")"; 
		instr += "\nbc1t label";
		break; 
	case(0):
		instr = "bclf "; 
		instr += "(PC + 4 + ";
		instr += getHex((convertImmediate(RelativeAddress) * 4)); 
		instr += ")"; 
		instr += "\nbc1f label"; 
		break; 
	default: 
		throw unKnownFIInstruction(); 
		break; 
	}
	return instr; 
}


/* Print I Format instructions*/
void FIFormat::printInstr()
{
	std::cout << "\nNumber:" << this->digits << "\n" << "Bits: " << this->bitfields << "\n"
		<< this->op << "|" <<  this->fmt << "|" << this->ft << "|" << this->immediate <<
		"\nFI-format\n" << "op == " << this->op << "\n" << "fmt == " << this->fmt << "\n" <<
		"ft == " << this->ft << "\nimmediate == " << this->immediate << "\n" <<
		"Instruction: " << getInstructions();

}