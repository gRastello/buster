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
	case 0x10:
		ADD();
		break;
	case 0x11:
		SUB();
		break;
	case 0x12:
		AND();
		break;
	case 0x13:
		OR();
		break;
	case 0x14:
		XOR();
		break;
	case 0x20:
		DROP();
		break;
	case 0x21:
		DUP();
		break;
	case 0x22:
		OVER();
		break;
	case 0x23:
		SWAP();
		break;
	case 0x30:
		STORE();
		break;
	case 0x31:
		FETCH();
		break;
	case 0x40:
		LIT();
		break;
	case 0x50:
		IF();
		break;
	case 0x60:
		CALL();
		break;
	case 0x61:
		EXIT();
		break;
	default: // We default to the HALT instruction.
		std::cout << "invalid opcode: 0x" << std::hex << unsigned(opcode)
		          << " (invoking HALT instead)" << std::endl;
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

// IF
// Jump to the address indicated by the following two bytes if the first element
// of the stack is zero. The first byte represents the higher nibble of the 
// address, the second one the lower nibble. The first element of the stack is 
// popped.
void Cpu::IF() {
	sp++; uint8_t head = read(sp);

	if (head == 0) {
		uint8_t hn = read(pc); pc++;
		uint8_t ln = read(pc);
		uint16_t addr = ((uint16_t)hn << 8) | (uint16_t)ln;

		pc = addr;
	} else {
		pc += 2;
	}
}

// CALL
// Pushes address of next instruction to the stack so that the higher nibble of
// the address is the first element of the stack and the lower nibble the 
// second. Then jumps to the address indicated by the following two bytes (again
// the first one is the higher nibble and the second one the lower).
void Cpu::CALL() {
	uint8_t sp_hn = (pc + 2) >> 8;
	uint8_t sp_ln = (pc + 2) & 0x00FF;
	write(sp, sp_ln); sp--;
	write(sp, sp_hn); sp--;

	uint8_t addr_hn = read(pc);
	uint8_t addr_ln = read(pc + 1);
	uint16_t addr = ((uint16_t)addr_hn << 8) | (uint16_t)addr_ln;
	pc = addr;
}

// EXIT
// Pops two bytes from the stack and jumps to that address. (as always the first
// byte is the higher nibble of the address and the second byte the lower 
// nibble).
void Cpu::EXIT() {
	sp++; uint8_t hn = read(sp);
	sp++; uint8_t ln = read(sp);
	pc = ((uint16_t)hn << 8) | (uint16_t)ln;
}

// ADD
// Add the first and second elements of the stack together and puts the sum at 
// the top of the stack. The two addends are popped.
void Cpu::ADD() {
	sp++; uint8_t a = read(sp);
	sp++; uint8_t b = read(sp);
	uint8_t result = a + b;

	write(sp, result); sp--;
}

// SUB
// Substract the second element of the stack from the first one and pushes the
// result to the stack (the operands are popped).
void Cpu::SUB() {
	sp++; uint8_t a = read(sp);
	sp++; uint8_t b = read(sp);
	uint8_t result = a - b;

	write(sp, result); sp--;
}

// AND
// Perform bitwise and with the first two elements of the stack and pushes the
// result to the stack (operands are popped).
void Cpu::AND() {
	sp++; uint8_t a = read(sp);
	sp++; uint8_t b = read(sp);
	uint8_t result = a & b;

	write(sp, result); sp--;
}

// OR
// Perform bitwise or with the first two elements of the stack and pushes the
// result to the stack (operands are popped).
void Cpu::OR() {
	sp++; uint8_t a = read(sp);
	sp++; uint8_t b = read(sp);
	uint8_t result = a | b;

	write(sp, result); sp--;
}

// XOR
// Perform bitwise xor with the first two elements of the stack and pushes the
// result to the stack (operands are popped).
void Cpu::XOR() {
	sp++; uint8_t a = read(sp);
	sp++; uint8_t b = read(sp);
	uint8_t result = a ^ b;

	write(sp, result); sp--;
}
