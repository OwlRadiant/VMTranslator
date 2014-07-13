#ifndef EXTENSION_H
#define EXTENSION_H
#include <string>
#include <sys/stat.h>


/* Ignore this warning, just here for teaching purposes
*DEPRECATED_WARNING: these function uses strtok(), which modifies the passed argument leaving only the string up until the first delimiter
*Update: updated function to no longer apply strtok() directly to the passed char*, leaving it intact; applies strtok() to a buffer instead
*/

//returns the file extension used, "" if none
std::string getFileExtension(const char* filename);

//returns the filename without extension, "" if none
std::string getFileName(char* filename);

//returns TRUE if file, FALSE if not
bool is_file(const char* path);

//??returns TRUE if directory, FALSE if not
bool is_dir(const char* path);

#endif