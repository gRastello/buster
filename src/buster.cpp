#include "buster.hpp"

#include <iostream>

Buster::Buster() { }
Buster::~Buster() { }

void Buster::run() {
	while (bus.cpu.running) bus.cpu.clock();

	std::cout << "The machine halted!" << std::endl;
	std::cout << "clockCount: " << bus.cpu.clockCount << std::endl;
}
