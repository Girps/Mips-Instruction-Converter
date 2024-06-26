#ifndef JFormat_h
#define JFormat_h
#include "FormatInstruction.h"

/*
	JFormat derived class of FormatInstruction class
	contains its own member immediate which represents a constant 
	denoting to a word-alligned address. Overrides printInstr() 
	and getInstruction as its instruction are distince from 
	other format types. 
*/ 


struct unKnownJinstruction:public std::runtime_error
{
	unKnownJinstruction(const char* msgArg); 
}; 

class JFormat :public FormatInstruction 
{
	public:
		JFormat(const std::string & digits, Base baseArg);
		~JFormat();
		void printInstr() override; 
		std::string getInstructions() override; 
		std::string getFullInstructions() override;
	protected: 
		// Data fields
		std::string immediate; 
		std::string getHex(int num); 
};


#endif