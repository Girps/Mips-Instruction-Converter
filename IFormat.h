#ifndef IFormat_h
#define IFormat_h
#include "FormatInstruction.h"

struct unKnownIInstr {}; 

class IFormat : public FormatInstruction
{
	// I Formats data fields
	std::string rs;
	std::string rt;
	std::string immediate;
	public:
		IFormat(const std::string &digits, Base baseArg); 
		~IFormat();
		std::string getInstructions() override;
		void printInstr() override;
}; 




#endif
