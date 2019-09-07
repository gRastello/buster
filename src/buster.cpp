#include "buster.hpp"

#include <iostream>
#include <fstream>

Buster::Buster() { }
Buster::~Buster() { }

void Buster::loadProgram(char *filename) {
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

void Buster::run() {
	while (bus.cpu.running) bus.cpu.clock();

	std::cout << "The machine halted!" << std::endl;
	std::cout << "clockCount: " << bus.cpu.clockCount << std::endl;
}
