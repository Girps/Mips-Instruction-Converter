#ifndef FormatInstruction_h
#define FormatInstruction_h
#include<string>
#include<iostream>

/*
	Abstract base class declaration. Every Mips instruction is denoted
	by bitfields with one field called op which are denoted from a 
	seqeunce of 8 digit Hex or 32 Binary digits.  
*/

struct invalidDigits : public std::runtime_error
{
	invalidDigits(const char* msgArg);
};
struct unKnownBase : public std::runtime_error
{
	unKnownBase(const char* msgArg);
};
struct unKnownBitField: public std::runtime_error
{
	unKnownBitField(const char* msgArg);
};

enum Base {Binary, Hex};
enum Form {RForm,JForm, IForm,FRForm, FIForm};

/*Abstract base class declaration */
class FormatInstruction 
{
	public: 
		virtual void printInstr() = 0;
		FormatInstruction(const std::string &nums, Base baseArg); 
		virtual ~FormatInstruction(); 
	protected:
		// Protected data fields
		int base; 
		std::string op;
		std::string digits; 
		std::string bitfields;
		// Protected function memebers
		void convertToBits(const std::string &digits); 
		std::string getRegisters(const std::string& digits);
		std::string getFPRegisters(const std::string& digits);
		virtual std::string getInstructions() = 0;
};

/*Free function declarations */
int getFormat(const std::string& bits);
std::string hextToBits(const std::string& nums); 
std::string bitToHex(const std::string& bits);
#endif 
