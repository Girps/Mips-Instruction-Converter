#include "FormatInstruction.h"

/*
	File: FormatInstruction.cpp define FormtInstruction type that will serve
	as an abstract base class with it data members and function members to 
	be inhierted by base classes: RFormat,IFormat and JFormat. Format Instruc-
	tion represents a 32-bit mips instruction that includes a registers, 
	instruction and address computation
*/

/*FormatInstruction constructor takes a sequence of digits and an Enum Base type 
	and initialzes data members with arguments */ 
FormatInstruction::FormatInstruction(const std::string &nums, Base baseArgs)
	:base{ baseArgs }, digits{nums}
{
	// Check base number is valid
	switch(base)
	{
	case(Hex): 
		if (nums.size() != 8 && nums.size() != 10 ) 
		{
			throw unKnownBase();
		}
		break; 
	case(Binary):
		if (nums.size() != 32)
		{
			throw unKnownBase();
		}
		break; 
	default: 
		throw unKnownBase(); 
		break; 
	}
	// Call protected functions initalize rest of memebers
	convertToBits(digits); // set bitfield
	op = bitfields.substr(0,6); 
}

FormatInstruction::~FormatInstruction() {}

/* Void setter function sets bitfield memeber to paramterized string */
void FormatInstruction::convertToBits(const std::string &nums ) 
{ 
	switch (this->base) 
	{
		case(0):	// Binary
			// Already converted
			this->bitfields = nums;
			break; 
		case(1):	// Hex
			 hextToBits(nums);
			break; 
		default: 
			throw unKnownBase(); 
			break; 
	}
}

/*Void setter function sets bitfields members to binary dights converted from hex sequence nums*/
void FormatInstruction::hextToBits(const std::string &hexString)
{
	std::string bits;
	std::string temp = hexString;
	// If size 10 remove first two chars 
	if (temp.size() == 10)
	{
		temp.erase(0, 1);
		temp.erase(0, 1);
	}
	// Convert 8 digit hexdecimal value to 32 bit instruciton
	for (auto it = temp.begin(); it != temp.end(); ++it) 
	{
		switch (std::toupper(*it)) 
		{
		case('0'):
			bits.append("0000");
				break; 
		case('1'):
			bits.append("0001");
				break;
		case('2'):
			bits.append("0010");
				break; 
		case('3'):
			bits.append("0011");
				break; 
		case('4'):
			bits.append("0100");
				break;
		case('5'):
			bits.append("0101");
				break; 
		case('6'):
			bits.append("0110");
				break;
		case('7'):
			bits.append("0111");
				break; 
		case('8'):
			bits.append("1000");
				break; 
		case('9'):
			bits.append("1001");
				break; 
		case('A'):
			bits.append("1010");
				break; 
		case('B'):
			bits.append("1011");
				break; 
		case('C'):
			bits.append("1100");
				break; 
		case('D'):
			bits.append("1101");
				break;
		case('E'):
			bits.append("1110");
				break; 
		case('F'):
			bits.append("1111");
				break;
		default: // Error 
			throw unKnownBitField();
				break; 
		}
	}
	this->bitfields = (bits); 
}


/*string returning function member converts sequence of bits into a register
	and return as a string */ 
std::string FormatInstruction::getRegisters(const std::string &bits) 
{
	// 32-bit Mips registers are 5 bits 
	if (bits.size() != 5) 
	{
		throw unKnownBitField(); 
	}

	int regValue{ 0 }; 
	regValue = std::stoi(bits,nullptr,2); 

	// Denote binary value to register to  be returned
	switch (regValue) 
	{
	case(0):
		return "$zero"; 
		break;
	case(1):
		return "$at"; 
		break; 
	case(2):
		return "$v0"; 
		break; 
	case(3):
		return "$v1"; 
		break; 
	case(4):
		return "$a0";
		break; 
	case(5):
		return "$a1";
		break;
	case(6):
		return "$a2"; 
		break;
	case(7):
		return "$a3"; 
		break; 
	case(8):
		return "$t0"; 
		break;
	case(9):
		return "$t1";
		break;
	case(10):
		return "$t2";
		break; 
	case(11):
		return "$t3";
		break;
	case(12):
		return "$t4";
		break; 
	case(13):
		return "$t5";
		break;
	case(14):
		return "$t6";
		break;
	case(15):
		return "$t7";
		break;
	case(16):
		return "$s0";
		break;
	case(17):
		return "$s1";
		break;
	case(18):
		return "$s2";
		break;
	case(19):
		return "$s3";
		break;
	case(20):
		return "$s4";
		break;
	case(21):
		return "$s5";
		break;
	case(22):
		return "$s6";
		break;
	case(23):
		return "$s7";
		break;
	case(24):
		return "$t8";
		break;
	case(25):
		return "$t9";
		break;
	case(26):
		return "$k0";
		break; 
	case(27):
		return "$k1";
		break; 
	case(28):
		return "$gp";
		break;
	case(29):
		return "$sp";
		break;
	case(30):
		return "$fp";
		break; 
	case(31):
		return "$ra";
		break;
	default:	// throw an exception
		throw unKnownBitField(); 
		break;
	}
}

/* string returning free function returns an interger denoting a Base type to
	determine the instruction format from a 6-bit sequence */
 int getFormat(const std::string& bits)
{
// If opcode is all zero 
	if (bits == "000000")
	{
	return RForm;
	} // JFormat have 2 or 3 opcode
	else if (bits == "000011" || bits == "000010")
	{
	return JForm;
	} // Other bit value is IFormat
	else
	{
		Form type = IForm; 
		switch (std::stoi(bits, nullptr, 2))
		{
		case(4):
			type = IForm;
			break;
		case(5):
			type = IForm;
			break;
		case(6):
			type = IForm;
			break;
		case(7):
			type = IForm;
			break;
		case(8):
			type = IForm;
			break;
		case(9):
			type = IForm;
			break;
		case(10):
			type = IForm;
			break;
		case(11):
			type = IForm;
			break;
		case(12):
			type = IForm;
			break;
		case(13):
			type = IForm;
			break;
		case(14):
			type = IForm;
			break;
		case(15):
			type = IForm;
			break;
		case(32):
			type = IForm;
			break;
		case(33):
			type = IForm;
			break;
		case(35):
			type = IForm;
			break;
		case(36):
			type = IForm;
			break;
		case(37):
			type = IForm;
			break;
		case(40):
			type = IForm;
			break;
		case(41):
			type = IForm;
			break;
		case(43):
			type = IForm;
			break;
		default: // throw error
			unKnownBitField();
			break;
		}
		return type; 
	}
}

/*string returning free function converts integers into a sequence of Hex digits 
	and returns as a string*/
std::string hextToBits(const std::string & nums)
{
	std::string bits;
	std::string temp = nums; 
	// check if size is 10 to truncate front bits
	if (temp.size() == 10) 
	{
		temp.erase(0, 1);
		temp.erase(0,1);
	}

	// Convert 8 digit hexdecimal value to 32 bit binary sequence
	for (auto it = temp.begin(); it != temp.end(); ++it)
	{
		switch (std::toupper(*it))
		{
		case('0'):
			bits.append("0000");
			break;
		case('1'):
			bits.append("0001");
			break;
		case('2'):
			bits.append("0010");
			break;
		case('3'):
			bits.append("0011");
			break;
		case('4'):
			bits.append("0100");
			break;
		case('5'):
			bits.append("0101");
			break;
		case('6'):
			bits.append("0110");
			break;
		case('7'):
			bits.append("0111");
			break;
		case('8'):
			bits.append("1000");
			break;
		case('9'):
			bits.append("1001");
			break;
		case('A'):
			bits.append("1010");
			break;
		case('B'):
			bits.append("1011");
			break;
		case('C'):
			bits.append("1100");
			break;
		case('D'):
			bits.append("1101");
			break;
		case('E'):
			bits.append("1110");
			break;
		case('F'):
			bits.append("1111");
			break;
		default: // Error 
			throw unKnownBitField();
			break;
		}
	}
	return bits;
}