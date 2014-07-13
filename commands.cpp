#include <string>
#include <iostream>
#include <sstream>
//ss << "" << std::endl;
void math_command(std::string command, std::stringstream& ss){

	//result = x + y;
	if (command == "add"){
		//Point to stack, decrement 1
		ss << "@SP" << std::endl;
		ss << "M = M - 1" << std::endl;

		//load stack address in A
		ss << "A = M" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1
		ss << "@SP" << std::endl;
		ss << "M = M - 1" << std::endl;

		//load stack address in A
		ss << "A = M" << std::endl;

		//replace "x" with result "x+y"
		ss << "M = M + D" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
	}
	//result = x - y;
	else if (command == "sub"){
		
		
	}

	//result = -y;
	else if (command == "neg"){
		
		
	}

	//result = !y
	else if (command == "not"){

		
	}

	//result = (x & y); bitwise and
	else if (command == "and"){
		
	}

	//result = (x | y); bitwise or
	else if (command == "or"){
		
	}

	//result = (x == y); (1 if equal, 0 if not)
	else if (command == "eq"){
		
		
	}
}



void mem_access_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){




}



void prog_flow_command(std::string command, std::string arg1, std::stringstream& ss){




}



void func_calling_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){





}