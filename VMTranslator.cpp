#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include "extension.h"
using namespace std;

int main(int argc, char** argv){
	//check given parameter; if file check for extension and parse it; if folder open folder and check individual files for extension, then parse them all into one .asm file
	if (argc != 2){
		cout << "VMTranslator needs exactly 1 argument to translate, either a .vm file or a folder containing .vm files.";
		return -1;
	}



	DIR* pdir = opendir("debug");
	dirent* pent = readdir(pdir);

	
	while (pent = readdir(pdir)){
		cout << pent->d_name << endl;
	}






	getchar();
	return 0;
}