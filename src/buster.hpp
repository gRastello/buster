#pragma once

#include "bus.hpp"

// The machine class. This is basically just a wrapper around the Bus class.
class Buster { 
public:
	Buster();
	~Buster();

	// Load a program in memory.
	void loadProgram(char* filename);

	// Run the machine.
	void run();

private:
	// The main bus.
	Bus bus;

#ifdef TEST
public:
	Bus *getBusPtr() { return &bus; }
#endif
};
