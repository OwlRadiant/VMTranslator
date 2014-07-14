#include <string>
#include <iostream>
#include <sstream>
#include "commands.h"


void math_command(std::string command, std::stringstream& ss){
	//use a salt when creating any label in a function to make it unique to that function
	static int salt = 0;

	//result = x + y;
	if (command == "add"){
		ss << std::endl << "//add" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//replace "x" with result "x + y"
		ss << "M = M + D" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
	}

	//result = x - y;
	else if (command == "sub"){
		ss << std::endl << "//sub" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//replace "x" with result "x - y"
		ss << "M = M - D" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
		
	}

	//result = (x & y); bitwise and
	else if (command == "and"){
		ss << std::endl << "//and" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//replace "x" with result "x & y"
		ss << "M = M & D" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
	}

	//result = (x | y); bitwise or
	else if (command == "or"){
		ss << std::endl << "//or" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//replace "x" with result "x | y"
		ss << "M = M | D" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
	}

	//result = -y;
	else if (command == "neg"){
		ss << std::endl << "//neg" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//negate variable "y" (decimal)
		ss << "M = -M" << std::endl;
		
		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
	}

	//result = !y
	else if (command == "not"){
		ss << std::endl << "//not" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//negate variable "y" (bitwise)
		ss << "M = !M" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
		
	}

	

	//result = (x == y); (1 if equal, 0 if not)
	else if (command == "eq"){
		ss << std::endl << "//eq" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//compute x - y to see if they're equal
		ss << "D = M - D" << std::endl;

		//M points to "x"; M also points to where the result is to be stored; we don't need "x" anymore so we init M = 0 (False = 0; True = -1)
		ss << "M = 0" << std::endl;

		//we will use 2 labels and 2 jumps for the if/else logic; if x != y go to END, if not negate(bitwise) M to produce True
		ss << "@EQ" + std::to_string(salt) << std::endl;
		ss << "D;JEQ" << std::endl;
		ss << "@END" + std::to_string(salt) << std::endl;
		ss << "0;JMP" << std::endl;

		ss << "(EQ" << std::to_string(salt)<< ")" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = !M" << std::endl;
		ss << "(END" << std::to_string(salt)<< ")" << std::endl;
		
		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		salt++;
	}

	//result = (x > y); true if x > y, else false
	else if (command == "gt"){
		ss << std::endl << "//gt" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//compute x - y to see if which is greater
		ss << "D = M - D" << std::endl;

		//M points to "x"; M also points to where the result is to be stored; we don't need "x" anymore so we init M = 0 (False = 0; True = -1)
		ss << "M = 0" << std::endl;

		//we will use 2 labels and 2 jumps for the if/else logic; if x > y, negate(bitwise) M to produce True, else go to END (M remains 0)
		ss << "@GT" + std::to_string(salt) << std::endl;
		ss << "D;JGT" << std::endl;
		ss << "@END" + std::to_string(salt) << std::endl;
		ss << "0;JMP" << std::endl;

		ss << "(GT" << std::to_string(salt)<< ")" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = !M" << std::endl;
		ss << "(END" << std::to_string(salt) << ")" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		salt++;
	}

	//result = (x < y); true if x < y, else false
	else if (command == "lt"){
		ss << std::endl << "//lt" << std::endl;
		//Point to stack, decrement 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//load "y" variable into D
		ss << "D = M" << std::endl;

		//Point to stack, decrement by 1, and load stack address into A
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;

		//compute x - y to see if which is greater
		ss << "D = M - D" << std::endl;

		//M points to "x"; M also points to where the result is to be stored; we don't need "x" anymore so we init M = 0 (False = 0; True = -1)
		ss << "M = 0" << std::endl;

		//we will use 2 labels and 2 jumps for the if/else logic; if x < y, negate(bitwise) M to produce True, else go to END (M remains 0)
		ss << "@LT" + std::to_string(salt) << std::endl;
		ss << "D;JLT" << std::endl;
		ss << "@END" + std::to_string(salt) << std::endl;
		ss << "0;JMP" << std::endl;

		ss << "(LT" << std::to_string(salt) << ")" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = !M" << std::endl;
		ss << "(END" << std::to_string(salt) << ")" << std::endl;

		//return stack pointer to top of stack
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		salt++;
	}
	else {
		ss << "Error arithmetic command" << std::endl;
	}
}
//ss << "" << std::endl;


void mem_access_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){

	//push command
	if (command == "push"){

		if (arg1 == "constant"){
			ss << std::endl << "//push constant " << arg2 << std::endl;
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;

		}
		else if (arg1 == "local"){
			ss << std::endl << "//push local " << arg2 << std::endl;

			//Selects local segment LCL + arg2, stores value in D
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@LCL" << std::endl;
			ss << "A = M + D" << std::endl;
			ss << "D = M" << std::endl;

			//Loads value stored in D in the stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			//Increment SP
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}

		else if (arg1 == "argument"){
			ss << std::endl << "//push argument " << arg2 << std::endl;

			//Selects argument segment ARG + arg2, stores value in D
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@ARG" << std::endl;
			ss << "A = M + D" << std::endl;
			ss << "D = M" << std::endl;

			//Loads value stored in D in the stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			//Increment SP
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}
		else if (arg1 == "this"){
			ss << std::endl << "//push this " << arg2 << std::endl;

			//Selects segment THAT + arg2, stores value in D
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@THIS" << std::endl;
			ss << "A = M + D" << std::endl;
			ss << "D = M" << std::endl;

			//Loads value stored in D in the stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			//Increment SP
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}
		else if (arg1 == "that"){
			ss << std::endl << "//push that " << arg2 << std::endl;

			//Selects segment THAT + arg2, stores value in D
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@THAT" << std::endl;
			ss << "A = M + D" << std::endl;
			ss << "D = M" << std::endl;

			//Loads value stored in D in the stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			//Increment SP
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}
		else if (arg1 == "temp"){
			ss << std::endl << "//push temp " << arg2 << std::endl;

			//Selects segment temp + arg2, stores value in D
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@R5" << std::endl;
			ss << "A = A + D" << std::endl;
			ss << "D = M" << std::endl;

			//Loads value stored in D in the stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			//Increment SP
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}
		else if (arg1 == "pointer"){
			ss << std::endl << "//push pointer " << arg2 << std::endl;

			//Selects segment pointer + arg2, stores value in D
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@R3" << std::endl;
			ss << "A = A + D" << std::endl;
			ss << "D = M" << std::endl;

			//Loads value stored in D in the stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			//Increment SP
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}
		else if (arg1 == "static"){
			ss << std::endl << "//push static " << arg2 << std::endl;

			//This is a trickier part, I get how it's implemented but I have no seen static used yet; will come back to this to understand better
			//Apparently static is used like a variable available to the whole file;
				/*static: According to the Hack machine language specification, when a new symbol is encountered for the first time in an assembly program, the assembler
				allocates a new RAM address to it, starting at address 16. This convention can be exploited to represent each static variable number j in a VM file f as the
				assembly language symbol f.j.For example, suppose that the file Xxx.vm contains the command push static 3. This command can be translated to the Hack
				assembly commands@Xxx.3 and D = M, followed by additional assembly code that pushes D’s value to the stack.This implementation of the static segment is
				somewhat tricky, but it works.*/

			//Get variable stored at that static address
			ss << "@" + filename + "." + arg2 << std::endl;
			ss << "D = M" << std::endl;

			//store variable in stack
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;

		}
	}

	//pop command
	if (command == "pop"){
		if (arg1 == "local"){
			ss << std::endl << "//pop local " << arg2 << std::endl;

			//Pops the highest stack variable in the D register
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;
			
			//Stores D in a temporary(NOT the temp segment) register
			ss << "@R15" << std::endl;
			ss << "M = D" << std::endl;

			//Selects address to insert D at (lol) and stores it in R14 
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@LCL" << std::endl;
			ss << "D = M + D" << std::endl;
			ss << "@R14" << std::endl;
			ss << "M = D" << std::endl;

			//Retrieves D and stores it at local "arg2"
			ss << "@R15" << std::endl;
			ss << "D = M" << std::endl;
			ss << "@R14" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			
			
		}
		else if (arg1 == "argument"){
			ss << std::endl << "//pop argument " << arg2 << std::endl;

			//Pops the highest stack variable in the D register
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;

			//Stores D in a temporary(NOT the temp segment) register
			ss << "@R15" << std::endl;
			ss << "M = D" << std::endl;

			//Selects address to insert D at (lol) and stores it in R14 
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@ARG" << std::endl;
			ss << "D = M + D" << std::endl;
			ss << "@R14" << std::endl;
			ss << "M = D" << std::endl;

			//Retrieves D and stores it at argument "arg2"
			ss << "@R15" << std::endl;
			ss << "D = M" << std::endl;
			ss << "@R14" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;
		}
		else if (arg1 == "this"){
			ss << std::endl << "//pop this " << arg2 << std::endl;

			//Pops the highest stack variable in the D register
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;

			//Stores D in a temporary(NOT the temp segment) register
			ss << "@R15" << std::endl;
			ss << "M = D" << std::endl;

			//Selects address to insert D at (lol) and stores it in R14 
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@THIS" << std::endl;
			ss << "D = M + D" << std::endl;
			ss << "@R14" << std::endl;
			ss << "M = D" << std::endl;

			//Retrieves D and stores it at this "arg2"
			ss << "@R15" << std::endl;
			ss << "D = M" << std::endl;
			ss << "@R14" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

		}
		else if (arg1 == "that"){
			ss << std::endl << "//pop that " << arg2 << std::endl;

			//Pops the highest stack variable in the D register
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;

			//Stores D in a temporary(NOT the temp segment) register
			ss << "@R15" << std::endl;
			ss << "M = D" << std::endl;

			//Selects address to insert D at (lol) and stores it in R14 
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@THAT" << std::endl;
			ss << "D = M + D" << std::endl;
			ss << "@R14" << std::endl;
			ss << "M = D" << std::endl;

			//Retrieves D and stores it at that "arg2"
			ss << "@R15" << std::endl;
			ss << "D = M" << std::endl;
			ss << "@R14" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;
		}
		else if (arg1 == "temp"){
			ss << std::endl << "//pop temp " << arg2 << std::endl;

			//Pops the highest stack variable in the D register
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;

			//Stores D in a temporary(NOT the temp segment) register
			ss << "@R15" << std::endl;
			ss << "M = D" << std::endl;

			//Selects address to insert D at (lol) and stores it in R14 
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@R5" << std::endl;
			ss << "D = A + D" << std::endl;
			ss << "@R14" << std::endl;
			ss << "M = D" << std::endl;

			//Retrieves D and stores it at temp "arg2"
			ss << "@R15" << std::endl;
			ss << "D = M" << std::endl;
			ss << "@R14" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;

			
		}
		else if (arg1 == "pointer"){
			ss << std::endl << "//pop pointer " << arg2 << std::endl;

			//Pops the highest stack variable in the D register
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;

			//Stores D in a temporary(NOT the temp segment) register
			ss << "@R15" << std::endl;
			ss << "M = D" << std::endl;

			//Selects address to insert D at (lol) and stores it in R14 
			ss << "@" + arg2 << std::endl;
			ss << "D = A" << std::endl;
			ss << "@R3" << std::endl;
			ss << "D = A + D" << std::endl;
			ss << "@R14" << std::endl;
			ss << "M = D" << std::endl;

			//Retrieves D and stores it at pointer "arg2"
			ss << "@R15" << std::endl;
			ss << "D = M" << std::endl;
			ss << "@R14" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;
		}
		else if (arg1 == "static"){
			ss << std::endl << "//pop static " << arg2 << std::endl;
			//This is a trickier part, I get how it's implemented but I have no seen static used yet; will come back to this to understand better
			//Apparently static is used like a variable available to the whole file;
			/*static: According to the Hack machine language specification, when a new symbol is encountered for the first time in an assembly program, the assembler
			allocates a new RAM address to it, starting at address 16. This convention can be exploited to represent each static variable number j in a VM file f as the
			assembly language symbol f.j.For example, suppose that the file Xxx.vm contains the command push static 3. This command can be translated to the Hack
			assembly commands@Xxx.3 and D = M, followed by additional assembly code that pushes D’s value to the stack.This implementation of the static segment is
			somewhat tricky, but it works.*/

			//store popped stack variable in D
			ss << "@SP" << std::endl;
			ss << "AM = M - 1" << std::endl;
			ss << "D = M" << std::endl;

			//store D at the static whatever
			ss << "@" + filename + "." + arg2 << std::endl;
			ss << "M = D" << std::endl;
		}
	}

}



void prog_flow_command(std::string command, std::string arg1, std::stringstream& ss){




}



void func_calling_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){





}