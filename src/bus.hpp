#pragma once

#include "cpu.hpp"

#include <array>
#include <cstdint>
#include <vector>

class Bus {
public:
	Bus();
	~Bus();

	// Print some memory cells.
	void print(std::vector<uint16_t> addresses);

	// Read and write to memory.
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);

	// Devices attached to the bus.
	std::array<uint8_t, 0xFFFF + 1> ram;
	Cpu cpu;
};
