#ifndef RFormat_h
#define RFormat_h
#include "FormatInstruction.h"


/*
	File: RFormat.h declare RFormat type that will inherits members
	of abstract type Format instruction and its function members.
	Derived class represents and R type of instruction that holds
	5 bitfields that represents a 32 bit instruction. 
*/


struct unKnownRFunction:public std::runtime_error
{
	unKnownRFunction(const char* msgArg);
};

/* Derived RFormat class inherits from abstract base class 
	FormatInstruction */ 
class RFormat : public FormatInstruction
{
	// Data fields of R Format instruction  
protected: 
	std::string rs;
	std::string rt;
	std::string rd;
	std::string shamt;
	std::string funct;
public:
	RFormat(const std::string& args, Base baseArg);
	virtual ~RFormat();
    std::string getInstructions()  override;
	std::string getFullInstructions() override;
	void printInstr() override;
};
#endif
