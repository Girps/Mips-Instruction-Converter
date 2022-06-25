#ifndef FormatInstruction_h
#define FormatInstruction_h
#include<string>
#include<iostream>

struct notEightDigits {};
struct unknownBase {};
struct unknownBitField {};


enum Base {Binary, Hex};
enum Form {RForm,JForm, IForm};
/*
	Abstract base class, cannot instantiate and its function memebers
	will be overridden by derived instances 
*/
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

/* Free function declarations*/
std::string getOp(const std::string& bits);

/* Getter function returns enum value denoting format type of the instruction*/
int getFormat(const std::string& bits);

/*String returning function converts hex decimal integers to bits*/
std::string hextToBits(const std::string& nums); 

#endif 
