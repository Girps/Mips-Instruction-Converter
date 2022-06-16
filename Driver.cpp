#include <iostream>
#include<bitset>
#include<string>
#include<sstream>

int main() 
{
	std::string s = "15"; 
	std::stringstream ss; 
	ss << std::hex << s;
	unsigned n; 
	std::string v = ss.str();
	std::cout << v; 
	ss >> n; 
	std::bitset<32> b(n);
	std::cout << b.to_string() << std::endl;
	int x = 0; 
	printf("Enter an integer to be convert into HEX");
	std::cin >> x; 
	std::cout << std::hex <<x; 
	return 0; 
}