#ifndef JFormat_h
#define JFormat_h
#include "FormatInstruction.h"

struct unknownJOp {}; 

class JFormat :public FormatInstruction 
{
	public:
		JFormat(const std::string & digits, Base baseArg);
		~JFormat();
		void printInstr() override; 
	protected: 
		// Data fields
		std::string immediate; 
		std::string getInstructions() override; 
		std::string getHex(int num); 
};


#endif