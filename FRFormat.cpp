#include "FRFormat.h"


/*Intialize memeber with string of numbers converted into bits 
	dependant on the Base enum */ 
FRFormat::FRFormat(const std::string &num, Base baseArg)
	:FormatInstruction(num,baseArg)
{
	// initalize floating point fields 
	std::string bits = this->bitfields;
	// Initlalize bitfields of mips instruction
	fmt = bitfields.substr(6, 5); // determines precision
	ft = bitfields.substr(11, 5);
	fs = bitfields.substr(16, 5);
	fd = bitfields.substr(21, 5);
	funct = bitfields.substr(26, 6);
	instruction = getInstructions();
}

// Destructor  
FRFormat::~FRFormat() {}

/*string returning function converts bit fields into floating point instruction 
	returns as string*/ 
std::string FRFormat::getInstructions()
{
	int func_Int = std::stoi(funct, nullptr, 2);
	int var = 0;
	// Get precision
	std::string prec = ((std::stoi(this->fmt, nullptr, 2) - 17)) ?
		("s ") : ("d "); 

	std::string instr;
	switch (func_Int) 
	{
	case(0): 
		instr += "add."; 
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
		break;
	case(1): 
		instr += "sub.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
			break;
	case(2):
		instr += "mul.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
		break;
	case(3):
		instr += "div.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
		break;
	case(4):
		instr += "sqrt.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(5):
		instr += "abs.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(6):
		instr += "mov.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(7):
		instr += "neg.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break;
	case(12):
		instr += "round.w."; 
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break;
	case(13):
		instr += "trunc.w.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(14):
		instr += "ceil.w.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(15):
		instr += "floor.w.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(18):
		instr += "movz.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		instr += " , ";
		instr += this->getRegisters(this->ft);
		break; 
	case(19):
		instr += "movn.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		instr += " , ";
		instr += this->getRegisters(this->ft);
		break; 
	case(32):
		instr += "cvt.s.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(33):
		instr += "cvt.d.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(34):
		instr += "cvt.w.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->fs);
		break; 
	case(50): 
		instr += "c.eq.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
		break; 
	case(60):
		instr += "c.lt.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
		break; 
	case(62):
		instr += "c.le.";
		instr += prec;
		instr += this->getFPRegisters(this->fd);
		instr += " , ";
		instr += this->getFPRegisters(this->ft);
		break; 
	}
	return instr; 
};

/*void returning function prints Floating point instruction */
void FRFormat::printInstr()
{
	std::cout << "Number:" << this->digits << "\n" << "Bits: " << this->bitfields << "\n"
		<< this->op << "|" << this->fmt << "|" << this->fs << "|" << this->ft << "|" << this->fd << "|" << this->funct
		<< "\n" << "FR-format\n" << "op == " << this->op << "\n" << "fmt == " << this->fmt <<
		"\nfs == " << this->fs << "\n" << "ft == " << this->ft << "\n" << "fd == " << this->fd 
		<< "\nfunct == " << this->funct << "\n" << "Instruction: " << this->instruction;
};