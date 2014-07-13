#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include "extension.h"
#include <vector>
#include "VM_parser.h"
#include <fstream>
using namespace std;


int main(int argc, char** argv){
	//check given parameter; if file check for extension and parse it; if folder open folder and check individual files for extension, then parse them all into one .asm file
	if (argc != 2){
		cout << "VMTranslator needs exactly 1 argument to translate, either a .vm file or a folder containing .vm files.";
		return -1;
	}
	stringstream ss;

	if (is_file(argv[1])){
		if (getFileExtension(argv[1]) == "vm"){
			parse_file((string)argv[1], ss);
		}
		else {
			cout << "Incorrect file extension (.vm).";
			getchar();
			return -2;
		}

		ofstream output_file;
		output_file.open(getFileName(argv[1]) + ".asm");
		string line;
		while (getline(ss, line)){
			output_file << line << endl;
		}
		output_file.close();
	}

	else if (is_dir(argv[1])){
		DIR* directory = opendir(argv[1]);
		dirent* pent;

		//loads all filenames in a vector<string>, then parse the ones with .vm extension
		vector<string> files;
		while (pent = readdir(directory)){
			files.push_back(pent->d_name);
		}

		for (unsigned int i = 0; i < files.size(); i++){
			if (getFileExtension(files[i].c_str()) == ".vm"){
				parse_file((string)argv[1] + "/" + files[i], ss);
			}
			
		}
	}

	else {
		cout << "Filename is invalid.";
		return -3;
	}
	
	
	//getchar();
	return 0;
}

/*DIR* pdir = opendir(".");
dirent* pent = readdir(pdir);


while (pent = readdir(pdir)){
cout << pent->d_name << endl;
}*/