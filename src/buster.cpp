#include "buster.hpp"

#include <iostream>
#include <fstream>

Buster::Buster() { }
Buster::~Buster() { }

void Buster::loadProgram(std::string filename) {
	// Read file to a string.
	std::ifstream file;
	file.exceptions(std::ifstream::failbit);

	try { file.open(filename, std::ios::binary); }
	catch (const std::exception &e) {
		std::cerr << "'" << filename 
		          << "' does not exists or is not accessible" << std::endl;
		throw;
	}

	std::string str((std::istreambuf_iterator<char>(file)),
	                (std::istreambuf_iterator<char>()));

	// Load it into memory.
	uint64_t i;
	for (i = 0; i < str.length(); i++) bus.ram[i] = str[i];
}

void Buster::print() {
	bus.cpu.print();
	if (!settings.watchedCells.empty()) 
		bus.print(settings.watchedCells);
}

void Buster::run() {
	if (settings.debugMode) print();

	while (bus.cpu.running) {
		if (settings.debugMode) {
			std::cout << "hit enter key to run the next instruction...";
			std::getchar();
		}

		bus.cpu.clock();

		if (settings.debugMode) print();
	}

	std::cout << "The machine halted!" << std::endl;
}
