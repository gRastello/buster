#pragma once

#include <array>
#include <cstdint>

#include "cpu.hpp"

class Bus {
public:
	Bus();
	~Bus();

	// Read and write to memory.
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);

	// Devices attached to the bus.
	std::array<uint8_t, 0xFFFF + 1> ram;
	Cpu cpu;
};
