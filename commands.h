#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <sstream>

//global variable for the filename, useful to the static segment
extern std::string filename;

//program initialization code, SP = 256, call Sys.init
void bootstrap_code_init(std::stringstream& ss);

//Translates the passed VM command into corresponding .hack instructions
void math_command(std::string command, std::stringstream& ss);

void mem_access_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss);

void prog_flow_command(std::string command, std::string arg1, std::stringstream& ss);

void func_calling_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss);

//returns a unique int each time it's called, useful for giving unique labels in commands
std::string label_salt();
#endif