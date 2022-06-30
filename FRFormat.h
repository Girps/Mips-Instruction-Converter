
#ifndef FRFormat_H
#define FRFormat_H
#include "FormatInstruction.h"
#include "RFormat.h"
/*
	FRFormat instruction derived class inherits from 
	FormatInstruction class and represents a floating 
	Point R format 32-bit instruction 
*/

struct unKnownFRFormatInstruction {}; 

class FRFormat: public FormatInstruction
{
	// floating point fields
	std::string fmt;
	std::string ft; 
	std::string fs; 
	std::string fd;
	std::string funct; 
	public: 
		FRFormat(const std::string& nums, Base baseArg);
		~FRFormat();
		std::string getInstructions()  override;
		void printInstr() override;
};



#endif 