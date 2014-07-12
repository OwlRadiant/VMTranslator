#ifndef EXTENSION_H
#define EXTENSION_H
#include <string>


/* Ignore this warning, just here for teaching purposes
*DEPRECATED_WARNING: these function uses strtok(), which modifies the passed argument leaving only the string up until the first delimiter
*Update: updated function to no longer apply strtok() directly to the passed char*, leaving it intact; applies strtok() to a buffer instead
*/

//returns the file extension used, NULL if none
std::string getFileExtension(char* filename);

//returns the filename without extension, NULL if none
std::string getFileName(char* filename);

#endif