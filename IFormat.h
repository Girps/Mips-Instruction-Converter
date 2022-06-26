#ifndef IFormat_h
#define IFormat_h
#include "FormatInstruction.h"

struct unKnownIInstr {}; 

enum AddressMode {ImmediateAddressing,BaseAddressing,RelativeAddress};

class IFormat : public FormatInstruction
{
	// I Formats data fields
	std::string rs;
	std::string rt;
	std::string immediate;
	int convertImmediate(AddressMode arg ); 
	std::string getHex(int num);
	public:
		IFormat(const std::string &digits, Base baseArg); 
		~IFormat();
		std::string getInstructions() override;
		void printInstr() override;
}; 
#endif
