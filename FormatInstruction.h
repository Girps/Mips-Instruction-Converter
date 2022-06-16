#ifndef FormatInstruction
#define FormatInstruction
#undef FormatInstruction

#include<string>
#include<sstream>
#include<bitset>

// struct throws execption 
struct notEightDigits {};

enum {Binary, Hex, Decimal};

/*
	Abstract base class, cannot instantiate and its function memebers
	will be overridden by derived instances 
*/
class FormatInstruction 
{
	public: 
		virtual std::string getFormat() = 0; 
		virtual void printInstr() = 0;
		std::string getOp; 
		std::string getRegisters(int digits);
	protected:
		std::string op;
		std::stringstream bitfields; 
};

/*
	RFormat class inherits from FormatInstruction
*/
class RFormat : public FormatInstruction 
{
	std::string rs; 
	std::string rt; 
	std::string rd;
	std::string shamt;
	std::string shamt; 
	public:
	
};

/*
	JFormat class inherits from FormatInstruction 
*/

class JFormat : public  FormatInstruction
{
	

};

/*
	IFormat class inherits form FormatInstruction
*/
class IFormat : public FormatInstruction 
{
	
};




#pragma once
#endif


