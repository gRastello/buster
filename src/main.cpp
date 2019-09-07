#include "buster.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argn, char *argv[]) {
	bool debugMode = false;

	// Store relevant arguments in a vector.
	std::vector<std::string> arguments;
	uint64_t i;
	for (i = 1; i < argn; i++) arguments.push_back(argv[i]);

	// Handle flags.
	std::vector<std::string>::iterator it;
	it = std::find(arguments.begin(), arguments.end(), "--debug");
	if (it != arguments.end()) {
		debugMode = true;
		arguments.erase(it);
	}
	
	// Check the number of arguments.
	if (arguments.size() != 1) {
		std::cerr << "usage: buster [--debug] FILE" << std::endl;
		std::exit(1);
	}

	// Make an instance of the stack machine.
	Buster machine;
	machine.debugMode = debugMode;

	try { machine.loadProgram(arguments[0]); }
	catch (...) {
		std::exit(1);
	}

	machine.run();
	
	return 0;
}
