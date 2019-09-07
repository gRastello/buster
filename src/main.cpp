#include "buster.hpp"

#include <iostream>

int main(int argn, char *argv[]) {
	// Check the number of arguments.
	if (argn != 2) {
		std::cerr << "usage: buster FILE" << std::endl;
		std::exit(1);
	}

	// Make an instance of the stack machine.
	Buster machine;

	try { machine.loadProgram(argv[1]); }
	catch (...) {
		std::exit(1);
	}

	machine.run();
	
	return 0;
}
