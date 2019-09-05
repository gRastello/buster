#include "bus.hpp"
#include "cpu.hpp"

#include <iostream>

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
	case 0x04:
		FETCH();
		break;
	case 0x05:
		DUP();
		break;
	case 0x06:
		OVER();
		break;
	case 0x07:
		SWAP();
		break;
	default: // We default to the HALT instruction.
		std::cout << "invalid opcode: 0x" << std::hex << unsigned(opcode)
		          << "(invoking HALT instead)" << std::endl;
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

// FETCH
// Store to the stack the value pointed to by the first two elements of the 
// stack (the first one representing the higher nibble and the second one the 
// lower of the address).
void Cpu::FETCH() {
	sp++; uint8_t hn = read(sp);
	sp++; uint8_t ln = read(sp);
	uint16_t addr = ((uint16_t)hn << 8) | (uint16_t)ln;

	write(sp, read(addr)); sp--;
}

// DUP
// Duplicate the first element of the stack and put it on top of the stack.
void Cpu::DUP() {
	uint8_t data = read(sp + 1);
	write(sp, data); sp--;
}

// OVER
// Push a copy of the second element of the stack to the top of the stack.
void Cpu::OVER() {
	uint8_t data = read(sp + 2);
	write(sp, data); sp--;
}

// SWAP
// Swap around the first and second elements of the stack.
void Cpu::SWAP() {
	uint8_t tmp = read(sp + 2);
	write(sp + 2, read(sp + 1));
	write(sp + 1, tmp);
}
