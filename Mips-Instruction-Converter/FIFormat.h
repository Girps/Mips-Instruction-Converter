
#ifndef FlFormat_h
#define FlFormat_H
#include "FormatInstruction.h"
#include "IFormat.h"

/*
	File: FlFormat.h decleration of the 
	Floating immediate format instruciton
	dervied class of FormatInstruction and
	I instruction 
*/


struct unKnownFIInstruction:public std::runtime_error 
{
	unKnownFIInstruction(const char* msgArg); 
};

/*
	FIFormat inheirts from IFormat
*/
class FIFormat : public IFormat  
{	
	std::string fmt; 
	std::string ft;
	public: 
	FIFormat(const std::string& nums, Base baseArg); 
	~FIFormat();
	std::string getInstructions() override;
	std::string getFullInstructions() override;
	void printInstr() override;
};



#endif 