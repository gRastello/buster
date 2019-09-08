#include "bus.hpp"

#include <iomanip>
#include <iostream>

Bus::Bus() {
	// Clear up the RAM.
	for (auto &x: ram) x = 0x00;

	cpu.connectToBus(this);
}

Bus::~Bus() { }

void Bus::print(std::vector<uint16_t> addresses) {
	std::cout << "* watched memory cells:" << std::endl;
	for (auto &addr: addresses) {
		std::cout << "  0x" << std::setw(4) << std::setfill('0')
		          << std::hex << unsigned(addr)
				  << ": 0x" << std::setw(2) << std::setfill('0')
				  << std::hex << unsigned(read(addr))
				  << std::endl;
	}
}

uint8_t Bus::read(uint16_t addr) {
	if (addr >= 0x0000 && addr <= 0xFFFF) return ram[addr];
	return 0x00;
}

void Bus::write(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr <= 0xFFFF) ram[addr] = data;
}
