#pragma once

#include "bus.hpp"

#include <vector>

// The machine class. This is basically just a wrapper around the Bus class.
class Buster { 
public:
	Buster();
	~Buster();

	// Load a program in memory.
	void loadProgram(std::string filename);

	// Run the machine.
	void run();

	// Print the current state of the machine.
	void print();

	// Settings.
	bool debugMode = true;
	std::vector<uint16_t> watchedCells;

private:
	// The main bus.
	Bus bus;

#ifdef TEST
public:
	Bus *getBusPtr() { return &bus; }
#endif
};
