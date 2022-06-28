#ifndef FormatInstruction_h
#define FormatInstruction_h
#include<string>
#include<iostream>

/*
	Abstract base class declaration. Every Mips instruction is denoted
	by bitfields with one field called op which are denoted from a 
	seqeunce of 8 digit Hex or 32 Binary digits.  
*/

struct notEightDigits {};
struct unKnownBase {};
struct unKnownBitField {};

enum Base {Binary, Hex};
enum Form {RForm,JForm, IForm};

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
		std::string instruction; 
		// Protected function memebers
		void convertToBits(const std::string &digits); 
		void hextToBits(const std::string& digts); 
		std::string getRegisters(const std::string& digits);
		virtual std::string getInstructions() = 0;
};

/*Free function declarations */
int getFormat(const std::string& bits);
std::string hextToBits(const std::string& nums); 

#endif 
