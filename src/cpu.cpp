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
	case 0x03:
		STORE();
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

// STORE
// Store the third element of the stack in memory address pointed to by the 
// first two elements of the stack (the first one representing the high nibble 
// and the second one the low nibble of the 16-bit array).
void Cpu::STORE() {
	sp++; uint8_t hn = read(sp);
	sp++; uint8_t ln = read(sp);
	uint16_t addr = ((uint16_t)hn << 8) | (uint16_t)ln;

	sp++; write(addr, read(sp));
}
