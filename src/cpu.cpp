#include "bus.hpp"
#include "cpu.hpp"

Cpu::Cpu() { }
Cpu::~Cpu() { }

void Cpu::clock() {
	// Read the opcode for the instruction.
	uint8_t opcode = bus->read(pc);
	pc++;

	switch (opcode) {
	case 0x00:
		HALT();
		break;
	default: // We default to the HALT instruction.
		HALT();
		break;
	}
}

uint8_t Cpu::read(uint16_t addr) {
	return bus->read(addr);
}

void Cpu::write(uint16_t addr, uint8_t data) {
	bus->write(addr, data);
}

// Instructions
void Cpu::HALT() {
	running = false;
}
