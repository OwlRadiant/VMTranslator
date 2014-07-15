#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "commands.h"
const std::vector<std::string> math = { "add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not" };
const std::vector<std::string> mem_access = { "push", "pop" };
const std::vector<std::string> prog_flow = {"label", "goto", "if-goto"};
const std::vector<std::string> func_calling = {"function", "call", "return"};

//this function takes each line and outputs to stringstream the equivalent .asm lines
void parse_line(std::string line, std::stringstream& ss){
	char* command = new char[20];
	char* arg1    = new char[20];
	char* arg2    = new char[20];
	int number;
	number = sscanf(line.c_str(), "%s %s %s", command, arg1, arg2);

	//checks if the command exists in the in one of the command lists specified above then apply that command with the given arguments
	if (std::find(math.begin(), math.end(), command) != math.end()) {
		math_command(command, ss);
	}

	else if (std::find(mem_access.begin(), mem_access.end(), command) != mem_access.end()){
		mem_access_command(command, arg1, arg2, ss);
	}

	else if (std::find(prog_flow.begin(), prog_flow.end(), command) != prog_flow.end()){
		prog_flow_command(command, arg1, ss);

	}

	else if (std::find(func_calling.begin(), func_calling.end(), command) != func_calling.end()){
		func_calling_command(command, arg1, arg2, ss);
	}
}

//This function only takes care of individual file reads and passes all the lines AND the stringstream off to parse_line();
//It's the same stringstream since all the files compile to one .asm file, so every write will be to only one file
void parse_file(std::string filename, std::stringstream& ss){
	std::ifstream input_file;
	input_file.open(filename);

	std::string line;

	while (getline(input_file, line)){
		parse_line(line, ss);
	}
}