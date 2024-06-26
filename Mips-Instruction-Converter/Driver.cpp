#include <iostream>
#include <memory>
#include "FormatInstruction.h"
#include "RFormat.h"
#include "JFormat.h"
#include "IFormat.h"
#include "FRFormat.h"
#include "FIFormat.h"
#include <crow.h>
/*
	Author: Jesse Jimenez
	Date: 6/27/2022
	Purpose: Enter a 8 digit hexadecimal value or 32-bit binary sequence to be converted into a
	32-bit MIPs instruction. 
*/

struct midware {
	
	midware(){}

	struct context{}; 

	void before_handle(crow::request& req, crow::response& res, context & ctx){
		
		
		
	}
	void after_handle(crow::request &req, crow::response& res, context& ctx)
	{
		if(res.code >= 400)
		{	
			res.set_header("Content-Type", "application/json");
			res.body = R"({"error": "Resource not found"})"; 
			res.end();
		}
	
	}	
};


int main() 
{
		std::string digit;
		std::string bit; 
		std::string op; 
		std::unique_ptr<FormatInstruction> smrtPtr;
		int sent = 0;
		int value = 0; 
		Base baseNumber = Hex; 
		
		crow::App<midware> app;
		
		//app.ssl_file("/etc/letsencrypt/live/mips-converter.com/cert.pem", "/etc/letsencrypt/live/mips-converter.com/privkey.pem");
			CROW_ROUTE(app, "/MIPS/<string>").methods(crow::HTTPMethod::GET) ([] ( std::string digit)
			{
					
				
					std::string digit_r;
					std::string bit_r;
					std::string op_r;
					std::unique_ptr<FormatInstruction> smrtPtr_r;
					std::string work = ""; 
					std::string instruction = ""; 
					int sent_r = 0;
					int value_r = 0;
					Base baseNumber_r = Hex;

					if (digit.size() == 8 || digit.size() == 10)
					{
						
						bit_r = hextToBits(digit);
						value_r = getFormat(bit_r);
						baseNumber_r = Hex;
					}
					else if (digit.size() == 32)
					{
						value_r = getFormat(digit);
						baseNumber_r = Binary;
					}
					// Check cases on the format 
					switch (value_r)
					{
					case(RForm):
						smrtPtr_r = std::make_unique<RFormat>(RFormat(digit, baseNumber_r));
						work = smrtPtr_r->getFullInstructions();
						instruction = smrtPtr_r->getInstructions();
						break;
					case(JForm):
						printf("J Format");
						smrtPtr_r = std::make_unique<JFormat>(JFormat(digit, baseNumber_r));
						work = smrtPtr_r->getFullInstructions();
						instruction = smrtPtr_r->getInstructions();
						break;
					case(IForm):
						printf("I Format");
						smrtPtr_r = std::make_unique<IFormat>(IFormat(digit, baseNumber_r));
						work = smrtPtr_r->getFullInstructions();
						instruction = smrtPtr_r->getInstructions();
						break;
					case(FRForm):
						printf("FR Format");
						smrtPtr_r = std::make_unique<FRFormat>(FRFormat(digit, baseNumber_r));
						work = smrtPtr_r->getFullInstructions();
						instruction = smrtPtr_r->getInstructions();
						break;
					case(FIForm):
						printf("FI Format");
						smrtPtr_r = std::make_unique<FIFormat>(FIFormat(digit, baseNumber_r));
						work = smrtPtr_r->getFullInstructions();
						instruction = smrtPtr_r->getInstructions();
						break;
					case((int)'q'):
						sent_r = 1;
						std::cout << "Program terminated\n";
						break;
					default:
						std::cout << "***ERROR input a valid 8 bit hex instruction ***\n";
						break;
					}

					crow::json::wvalue x; 

					x["work"] = work; 
					x["instruction"] = instruction; 
					auto response = crow::response(x);
					response.add_header("Access-Control-Allow-Origin", "https://www.mips-converter.com"); 
				

			
					// get the string 
					return response; 
			}); 



			app.port(18080).multithreaded().run(); 
}
