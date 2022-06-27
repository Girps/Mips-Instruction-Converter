#include "FormatInstruction.h"



FormatInstruction::FormatInstruction(const std::string &nums, Base baseArgs)
	:base{ baseArgs }, digits{nums}
{
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

/*Void setter function sets bitfields members to binary dights from hex*/
void FormatInstruction::hextToBits(const std::string &nums)
{
	std::string bits;
	std::string temp = nums;
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


// Getter function converts bits into registers and returns 
std::string FormatInstruction::getRegisters(const std::string &bits) 
{
	if (bits.size() > 5) 
	{
		throw unKnownBitField(); 
	}
	int regValue{ 0 }; 
	regValue = std::stoi(bits,nullptr,2); 
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

/* Getter function returns enum value denoting format type of the instruction*/
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

std::string getOp(const std::string& bits)
{
	std::string temp;
	for (auto it = bits.begin(); it != bits.end(); ++it)
	{
		temp.push_back(*it);
	}
	return temp;
}

/*Void setter function sets bitfields members to binary dights from hex */
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
	return bits;
}