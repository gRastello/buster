#include "stacky.hpp"

#include <iostream>

Stacky::Stacky() { }
Stacky::~Stacky() { }

void Stacky::run() {
	while (bus.cpu.running) {
		bus.cpu.clock();
	}

	std::cout << "The machine halted!" << std::endl;
}
