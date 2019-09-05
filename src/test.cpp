#define TEST

#include "stacky.cpp"
#include "bus.cpp"
#include "cpu.cpp"

#include <iostream>
#include <vector>
#include <string>

struct Test {
	std::string name;
	bool (* test)();
};

bool runTest(Test test) {
	bool result = (*test.test)();

	if (result) std::cout << test.name << ": PASS" << std::endl;
	return result;
}

void reportMismatch(std::string testName, std::string expected, uint8_t found) {
	std::cout << testName << ": FAILED" << std::endl;
	std::cout << "  expected " << expected << " but found 0x" 
	          << std::hex << unsigned(found) << std::endl;
}

// Test the LIT instruction.
bool testLIT() {
	Stacky machine;
	Bus* bus = machine.getBusPtr();

	// Initialize some ram.
	bus->ram[0x0000] = 0x01; // LIT
	bus->ram[0x0001] = 0x03;
	bus->ram[0x0002] = 0x01; // LIT
	bus->ram[0x0003] = 0xFE;
	bus->ram[0x0004] = 0x00; // HALT

	// Run the machine.
	while(bus->cpu.running) bus->cpu.clock();

	// Check the results.
	uint16_t sp = bus->cpu.getSP();

	sp++;
	if (bus->read(sp) != 0xFE) {
		reportMismatch("LIT", "0xFE", bus->read(sp));
		return false;
	}

	sp++;
	if (bus->read(sp) != 0x03) {
		reportMismatch("LIT", "0x03", bus->read(sp));
		return false;
	}

	return true;
}

// Test the DROP instruction.
bool testDROP() {
	Stacky machine;
	Bus* bus = machine.getBusPtr();

	// Initialize some ram.
	bus->ram[0x0000] = 0x01; // LIT
	bus->ram[0x0001] = 0x00;
	bus->ram[0x0002] = 0x02; // DROP
	bus->ram[0x0004] = 0x00; // HALT

	// Run the machine.
	while(bus->cpu.running) bus->cpu.clock();

	// Check the results.
	uint16_t sp = bus->cpu.getSP();

	if (sp != 0xFFFF) {
		reportMismatch("DROP", "0xFFFF", sp);
		return false;
	}

	return true;
}

// Test the STORE function.
bool testSTORE() {
	Stacky machine;
	Bus* bus = machine.getBusPtr();

	//Initialize some ram.
	bus->ram[0x0000] = 0x01; // LIT
	bus->ram[0x0001] = 0x11;
	bus->ram[0x0002] = 0x01; // LIT
	bus->ram[0x0003] = 0x0E;
	bus->ram[0x0004] = 0x01; // LIT
	bus->ram[0x0005] = 0xA0;

	bus->ram[0x0006] = 0x03; // STORE
	bus->ram[0x0007] = 0x00; // HALT

	// Run the machine.
	while(bus->cpu.running) bus->cpu.clock();

	// Check results.
	if (bus->read(0xA00E) != 0x11) {
		reportMismatch("STORE", "0x11", bus->read(0xA00E));
		return false;
	}

	return true;
}

int main() {
	bool allPass = true;
	std::vector<Test> allTests = {
		{ "LIT",   &testLIT },
		{ "DROP",  &testDROP },
		{ "STORE", &testSTORE },
	};

	// Execute the tests.
	for (auto &test: allTests) allPass = runTest(test);

	if (allPass) return 0;
	return 1;
}
