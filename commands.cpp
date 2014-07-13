#include <string>
#include <iostream>
#include <sstream>

void math_command(std::string command, std::stringstream& ss){

	//result = x + y;
	if (command == "add"){
		//Point to stack, pop "y" value into D
		ss << "@SP" << std::endl;
		ss << "A - 1" << std::endl;
		ss << "D = M" << std::endl;

		//Go to "x" value, replace it's value with "x + y"; exactly same effect as popping and pushing, less commands
		ss << "A - 1" << std::endl;
		ss << "M = M + D" << std::endl;

		//return SP to top of stack
		ss << "A + 1" << std::endl;
	}
	//result = x - y;
	else if (command == "sub"){
		
		//Point to stack, pop "y" value into D
		ss << "@SP" << std::endl;
		ss << "A - 1" << std::endl;
		ss << "D = M" << std::endl;

		//Go to "x" value, replace it's value with "x - y"; exactly same effect as popping and pushing, less commands
		ss << "A - 1" << std::endl;
		ss << "M = M - D" << std::endl;

		//return SP to top of stack
		ss << "A + 1" << std::endl;
	}

}



void mem_access_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){




}



void prog_flow_command(std::string command, std::string arg1, std::stringstream& ss){




}



void func_calling_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){





}