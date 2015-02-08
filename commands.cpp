#include <string>
#include <iostream>
#include <sstream>
#include "commands.h"

static int salt = 0;
static std::string function_name = "empty";

//program initialization code, SP = 256, call (!!!!!!!!!!FUCKING VM CALL NOT JMP) Sys.init
void bootstrap_code_init(std::stringstream& ss){
	ss << "//Init bootstrap code" << std::endl;
	ss << "@256" << std::endl;
	ss << "D = A" << std::endl;
	ss << "@SP" << std::endl;
	ss << "M = D" << std::endl;

	func_calling_command("call", "Sys.init", "0", ss);
}

void math_command(std::string command, std::stringstream& ss){
	//use a salt when creating any label in a function to make it unique to that function
	

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

			// This is a trickier part, I get how it's implemented but I have not seen
			// static used yet; will come back to this to understand better Apparently
			// static is used like a variable available to the whole file;

			/* static: According to the Hack machine language specification, when a new
			symbol is encountered for the first time in an assembly program, the assembler
			allocates a new RAM address to it, starting at address 16. This convention can
			be exploited to represent each static variable number j in a VM file f as the
			assembly language symbol f.j.For example, suppose that the file Xxx.vm contains
			the command push static 3. This command can be translated to the Hack assembly
			commands@Xxx.3 and D = M, followed by additional assembly code that pushes D's
			value to the stack.This implementation of the static segment is somewhat tricky,
			but it works. */

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

			// This is a trickier part, I get how it's implemented but I have not seen
			// static used yet; will come back to this to understand better Apparently
			// static is used like a variable available to the whole file;

			/* static: According to the Hack machine language specification, when a new
			symbol is encountered for the first time in an assembly program, the assembler
			allocates a new RAM address to it, starting at address 16. This convention can
			be exploited to represent each static variable number j in a VM file f as the
			assembly language symbol f.j.For example, suppose that the file Xxx.vm contains
			the command push static 3. This command can be translated to the Hack assembly
			commands@Xxx.3 and D = M, followed by additional assembly code that pushes D'
			value to the stack.This implementation of the static segment is somewhat tricky,
			but it works. */

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
	if (command == "label"){
		ss << std::endl;
		ss << "(" + function_name +"$" + arg1 + ")" << std::endl;
	}
	else if (command == "goto"){
		ss << "@" + function_name + "$" + arg1 << std::endl;
		ss << "0; JMP" << std::endl;
	}
	else if (command == "if-goto"){
		ss << std::endl << "//if-goto " << arg1 << std::endl;
		//pop stack value
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;
		ss << "D = M" << std::endl;

		//if D == 0 ignore jump; else if D != 0 jump to "label" 
		ss << "@" + function_name + "$" + arg1 << std::endl;
		ss << "D; JNE" << std::endl;
		
	}

}



void func_calling_command(std::string command, std::string arg1, std::string arg2, std::stringstream& ss){
	if (command == "function"){
		//sets the function name for any labels that are generated while in the function
		function_name = arg1;

		ss << std::endl << "//function " + arg1 << std::endl;
		ss << "("  + arg1 + ")" << std::endl;
		for (int i = 0; i < std::stoi(arg2); i++){
			ss << "@0" << std::endl;
			ss << "D = A" << std::endl;
			ss << "@SP" << std::endl;
			ss << "A = M" << std::endl;
			ss << "M = D" << std::endl;
			ss << "@SP" << std::endl;
			ss << "M = M + 1" << std::endl;
		}
	}
	else if (command == "call"){
		//calling function after "arg2" arguments have been pushed on the stack
		ss << std::endl << "//call " + arg1 + " " + arg2<< std::endl;

		//push return address to stack
		ss << "@RETURN_ADDRESS_" + arg1 + "_" + std::to_string(salt) << std::endl;
		ss << "D = A" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = D" << std::endl;
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;
		
		//push LCL
		ss << "@LCL" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = D" << std::endl;
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		//push ARG
		ss << "@ARG" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = D" << std::endl;
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		//push THIS
		ss << "@THIS" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = D" << std::endl;
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		//push THAT
		ss << "@THAT" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@SP" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = D" << std::endl;
		ss << "@SP" << std::endl;
		ss << "M = M + 1" << std::endl;

		//ARG = SP-n-5 ( n = number of arguments)
		ss << "@SP" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@" + arg2 << std::endl;
		ss << "D = D - A" << std::endl;
		ss << "@5" << std::endl;
		ss << "D = D - A" << std::endl;
		ss << "@ARG" << std::endl;
		ss << "M = D" << std::endl;

		//LCL = SP
		ss << "@SP" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@LCL" << std::endl;
		ss << "M = D" << std::endl;
		

		//goto f (arg1)
		ss << "@" + arg1 << std::endl;
		ss << "0; JMP" << std::endl;
		
		//(return-address)
		ss << "(RETURN_ADDRESS_" + arg1 + "_" + std::to_string(salt) + ")" << std::endl;

		//needed for the unique label ID of the return address
		salt++;

	}
	else if (command == "return"){

		//returns program execution back to return-address with the computed value on the top of the stack
		ss << std::endl << "//return " << std::endl;

		//ss << std::endl << "//FRAME = LCL (just store LCL anywhere, R13 here)" << std::endl;
		ss << "@LCL" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@R13" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//RET = *(FRAME - 5)  store return address somewhere (R14 here)" << std::endl;
		ss << "@R13" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@5" << std::endl;
		ss << "A = D - A" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@R14" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//*ARG = pop()    pop the LOCAL/CURRENT stack into *ARG 0, which will be the top of the global stack(by global I mean at the scope of the caller function) when function returns " << std::endl;
		ss << "@SP" << std::endl;
		ss << "AM = M - 1" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@ARG" << std::endl;
		ss << "A = M" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//SP = ARG + 1    move stack pointer back to the top of the caller function's stack" << std::endl;
		ss << "@ARG" << std::endl;
		ss << "D = M + 1" << std::endl;
		ss << "@SP" << std::endl;
		ss << "M = D" << std::endl;
		
		//move back all the registers as they were before the call
		//ss << std::endl << "//THAT = *(FRAME - 1)" << std::endl;
		ss << "@R13" << std::endl;
		ss << "A = M - 1" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@THAT" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//THIS = *(FRAME - 2)" << std::endl;
		ss << "@R13" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@2" << std::endl;
		ss << "A = D - A" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@THIS" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//ARG = *(FRAME - 3)" << std::endl;
		ss << "@R13" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@3" << std::endl;
		ss << "A = D - A" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@ARG" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//LCL = *(FRAME - 4)" << std::endl;
		ss << "@R13" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@4" << std::endl;
		ss << "A = D - A" << std::endl;
		ss << "D = M" << std::endl;
		ss << "@LCL" << std::endl;
		ss << "M = D" << std::endl;

		//ss << std::endl << "//goto RET (stored previously in R14)" << std::endl;
		ss << "@R14" << std::endl;
		ss << "A = M" << std::endl;
		ss << "0; JMP" << std::endl;
	}


}
