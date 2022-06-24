#ifndef RFormat_h
#define RFormat_h
#include "FormatInstruction.h"

struct unknownFunction {};

/*
	RFormat class inherits from FormatInstruction
*/
class RFormat : public FormatInstruction
{
	// Data fields of R Format instruction  
	std::string rs;
	std::string rt;
	std::string rd;
	std::string shamt;
	std::string funct;
public:
	RFormat(const std::string& args, Base baseArg);
	~RFormat();
    std::string getInstructions()  override;
	void printInstr() override;
};
#endif
