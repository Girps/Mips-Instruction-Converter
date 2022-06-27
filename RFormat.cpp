#include "RFormat.h"
#include<string>

/* RFormat constructor calls base constructor and intializes data memebers */
RFormat::RFormat(const std::string &nums,Base baseArg)
	:FormatInstruction(nums,baseArg)
{
	// Now initalize derived data members
	std::string bits = this->bitfields; 
	// Initlalize bitfields of mips instruction
	rs = bitfields.substr(6,5);
	rt = bitfields.substr(11,5);
	rd = bitfields.substr(16,5);
	shamt = bitfields.substr(21, 5);
	funct = bitfields.substr(26, 6); 
	instruction = getInstructions(); 
}

// Destructor
RFormat::~RFormat() {}

/*Overidden string returning funciton, checks funct code instructions and returns its instruction*/ 
 std::string RFormat::getInstructions() 
{
	 int func_Int = std::stoi(funct,nullptr,2);
	 int var = 0; 
	 std::string instr; 
	 // Convert binary number to int 
	 switch (func_Int) 
	 {
	 case(0):  
		 instr = "sll "; 
		 instr += this->getRegisters(this->rd); 
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 instr += " , ";
		 instr += std::to_string(std::stoi(this->shamt,nullptr,2));
		 break;
	 case(2):
		 instr = "srl ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 instr += " , ";
		 instr += std::to_string(std::stoi(this->shamt,nullptr,2));
		 break; 
	 case(3): 
		 instr += "sra ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 instr += " , ";
		 instr += std::to_string(std::stoi(this->shamt, nullptr, 2));
		 break; 
	 case(4): 
		 instr += "sllv ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 break; 
	 case(6): 
		 instr += "srlv ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 break;
	 case(7): 
		 instr += "srav ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 break;
	 case(8): 
		 instr += "jr ";
		 instr += this->getRegisters(this->rs);
		 break; 
	 case(9): 
		 instr += "jalr ";
		 instr += this->getRegisters(this->rs); 
		 // second variant
		 instr += "\n"; 
		 instr += "jalr"; 
		 instr += this->getRegisters(this->rd);
		 instr += " , "; 
		 instr += this->getRegisters(this->rs); 
		 break; 
	 case(12):	
		 instr = "syscall"; 
		 break; 
	 case(16): 
		 instr = "mfhi "; 
		 instr += this->getRegisters(this->rd);
		 break;
	 case(17):
		 instr = "mthi ";
		 instr += this->getRegisters(this->rs);
		 break; 
	 case(18): 
		 instr = "mflo ";
		 instr += this->getRegisters(this->rd); 
		 break; 
	 case(19): 
		 instr = "mtlo ";
		 instr += this->getRegisters(this->rs);
		 break; 
	 case(24): 
		 instr = "mult "; 
		 instr += this->getRegisters(this->rs);
		 instr += " , "; 
		 instr += this->getRegisters(this->rt); 
		 break; 
	 case(25):
		 instr = "multu ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(26): 
		 instr = "div ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(27): 
		 instr = "divu ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(32):
		 instr = "add ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , "; 
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(33): 
		 instr = "addu ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(34):
		 instr = "sub ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(35):
		 instr = "subu ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(36): 
		 instr = "and ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(37): 
		 instr = "or ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(38):
		 instr = "xor ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(39): 
		 instr = "nor ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(42): 
		 instr = "slt ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break; 
	 case(43):
		 instr = "sltu ";
		 instr += this->getRegisters(this->rd);
		 instr += " , ";
		 instr += this->getRegisters(this->rs);
		 instr += " , ";
		 instr += this->getRegisters(this->rt);
		 break;
	 default: // unknownFunction bit field
		 throw unKnownRFunction();
		 break;
	 }
	 this->instruction = instr; 
	 return instr; 
}

/* Overloaded function memeber prints instruction of 8 bit instruction*/
 void RFormat::printInstr() 
 {
	 std::cout << "Hex:" << this->digits << "\n" << "Bits: " << this->bitfields << "\n"
		 << this->op << "|" << this->rs << "|" << this->rt << "|" << this->rd << "|" << this->shamt
		 << "|" << this->funct << "\n" << "R-format\n" <<"op == " << this->op << "\n" <<
		 "rs == " << this->rs << "\n" << "rt == " << this->rt
		 << "\n" << "rd == " << this->rd << "\n" << "shamt == " << this->shamt
		 << "\nfunct == " << this->funct << "\n" << "Instruction: " << this->instruction; 
 }