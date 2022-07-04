#ifndef IFormat_h
#define IFormat_h
#include "FormatInstruction.h"

/*
	File: IFomat.h 
	IFormat declaration public inherits from abstract
	FormatInstruction class, While contains its own 3 
	bit fields. File contains enums AddressMode as I-
	type instruction have 3 types of addressing modes
	that determine the string instruction sequence. 
*/

struct unKnownIInstruction : public std::runtime_error
{
	unKnownIInstruction(const char* msgArg); 
}; 

/* Derived class IFormat declaration inherits from abstract
	base class FormatInstruction*/
class IFormat : public FormatInstruction
{
	// I Formats data fields
	
	// Inheirted memebers for FI type
	protected: 
	std::string rt;
	std::string rs;
	std::string immediate;
	int convertImmediate( ); 
	std::string numsToBits(int nums); 
	public:
		IFormat(const std::string &digits, Base baseArg); 
		virtual ~IFormat();
		std::string getInstructions() override;
		void printInstr() override;
}; 
#endif
