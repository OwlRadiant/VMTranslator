#include <string>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>

std::string getFileExtension(const char *filename){
	//check for non-NULL pointer
	if (filename == NULL) return "";

	//since strtok modifies the parameter it's been passed, we copy *filename to a temporary buffer
	char* buffer = new char[strlen(filename) + 1];
	strcpy(buffer, filename);

	std::string extension;
	char* temp = strtok(buffer, ".");

	//counts the number of parts in filename separated by dots; if count <= 1 then file has no extension and function returns NULL
	int count = 0;
	
	//use temp to check for file end before comitting result of strtok to extension
	while (temp != NULL){
		count++;
		temp = strtok(NULL, ".");
		if (temp != NULL) extension = temp;
	}

	if (count <= 1) return "";

	delete[] buffer;
	return extension;
}

std::string getFileName(char* filename){
	
	//checks correct function usage
	if (filename == NULL) return "";

	char* buffer = new char[strlen(filename) + 1];
	strcpy(buffer, filename);

	//vector to store the parts of the filename
	std::vector <std::string> file_parts;
	char* part = strtok(buffer, ".");

	//stores each part of the filename between dots
	while (part != NULL){
		file_parts.push_back((std::string) part);
		part = strtok(NULL, ".");
	}

	//combines all string except the extension into the final filename
	std::string result;

	for (int i = 0; i < int(file_parts.size() - 1); i++){             //x.size() is of type size_t, operator "<" can't handle 2 different types in comparison, so we do explicit conversion
		result += file_parts[i];
		if (i < int(file_parts.size() - 2)) result += ".";
	}

	delete[] buffer;
	return result;
}

bool is_file(const char* path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}