#pragma once

#include "bus.hpp"

// The machine class. This is basically just a wrapper around the Bus class.
class Stacky { 
public:
	Stacky();
	~Stacky();

	// Run the machine.
	void run();

private:
	// The main bus.
	Bus bus;
};
