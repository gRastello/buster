#include "generator.hpp"

#include <string>
#include <unordered_map>

Generator::Generator(std::vector<std::shared_ptr<Statement>> _statements) {
	statements = _statements;
}

Generator::~Generator() { }

std::vector<uint8_t> Generator::generate() {
	std::vector<uint8_t> code;

	// Get all jump locations.
	std::unordered_map<std::string, uint16_t> jumpLocations;
	size_t i = 0;
	for (auto &statement: statements) {
		if (statement->label != "") jumpLocations[statement->label] = i;

		// Increase the counter by the number of bytes that the instruction 
		// occupies.
		std::shared_ptr<ImmediateStmt> imm =
			std::dynamic_pointer_cast<ImmediateStmt>(statement);
		std::shared_ptr<LabelStmt> label =
			std::dynamic_pointer_cast<LabelStmt>(statement);

		if (imm  ) { i += 2; continue; }
		if (label) { i += 3; continue; }
		i++;
	}
	
	// Actually generates the code.
	for (auto &statement: statements) {
		// Specialize the pointer.
		std::shared_ptr<NoOperandStmt> noop = 
			std::dynamic_pointer_cast<NoOperandStmt>(statement);
		std::shared_ptr<ImmediateStmt> imm =
			std::dynamic_pointer_cast<ImmediateStmt>(statement);
		std::shared_ptr<LabelStmt> label =
			std::dynamic_pointer_cast<LabelStmt>(statement);

		code.push_back(opcodes[statement->instruction]);

		if (imm  ) code.push_back(imm->operand);
		if (label) {
			code.push_back(jumpLocations[label->operand] & 0xFF00);
			code.push_back(jumpLocations[label->operand] & 0x00FF);
		}
	}

	return code;
}
