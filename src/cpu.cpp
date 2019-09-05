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
	case 0x01:
		LIT();
		break;
	case 0x02:
		DROP();
		break;
	default: // We default to the HALT instruction.
		HALT();
		break;
	}

	// Increase the clock counter.
	clockCount++;
}

uint8_t Cpu::read(uint16_t addr) {
	return bus->read(addr);
}

void Cpu::write(uint16_t addr, uint8_t data) {
	bus->write(addr, data);
}

/* ************
 * Instructions 
 * ************ */

// HALT
// Stops the machine.
void Cpu::HALT() {
	running = false;
}

// LIT
// Loads an immediate value on the stack.
void Cpu::LIT() {
	uint8_t data = read(pc);
	pc++;

	write(sp, data);
	sp--;
}

// DROP
// Drop an element from the stack.
void Cpu::DROP() {
	sp++;
}
