#pragma once

#include <cstdint>

class Bus;

class Cpu { 
public:
	Cpu();
	~Cpu();

	// Cpu's status.
	bool running = true;

	// Perform a clock (in the case of Stacky a whole instruction).
	void clock();
	uint64_t clockCount = 0;

	// Connect to the bus.
	void connectToBus(Bus *x) { bus = x; }

private:
	// Registers.
	uint16_t pc = 0x0000; // Program counter.
	uint16_t sp = 0xFFFF; // Stack pointer.

	// Connection to the bus.
	Bus* bus;
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);

	// Instructions.
	void HALT();
	void ADD();   void SUB(); void AND();  void OR(); void XOR();
	void DROP();  void DUP(); void OVER(); void SWAP();
	void STORE(); void FETCH();
	void LIT();
	void IF();
	void CALL();  void EXIT();

#ifdef TEST
public:
	uint16_t getPC() { return pc; }
	uint16_t getSP() { return sp; }
#endif
};
