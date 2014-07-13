#ifndef VMPARSER_H
#define VMPARSER_H
#include <string>
#include <sstream>


//Parses given line from the file parser
void parse_line(std::string line, std::stringstream& ss);

//parses the given file and returns it in the stringstream specified
void parse_file(std::string filename, std::stringstream& ss);


#endif