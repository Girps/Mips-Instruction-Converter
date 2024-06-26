
#ifndef FRFormat_H
#define FRFormat_H
#include "FormatInstruction.h"
#include "RFormat.h"

/*
	FRFormat instruction derived class inherits from 
	RFormat class and represents a floating 
	Point R format 32-bit instruction 
*/

struct unKnownFRFormatInstruction: public std::runtime_error
{
	unKnownFRFormatInstruction(const char* msgArg); 
}; 

class FRFormat: public RFormat
{
	// floating point fields
	std::string fmt;
	std::string ft; 
	std::string fs; 
	std::string fd;
	public: 
		FRFormat(const std::string& nums, Base baseArg);
		~FRFormat();
		std::string getInstructions()  override;
		std::string getFullInstructions() override;
		void printInstr() override;
};



#endif 