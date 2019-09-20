#pragma once

#include "statement.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

class Generator {
public:
	Generator(std::vector<std::shared_ptr<Statement>> _statements);
	~Generator();

	// Generate Buster machine code.
	std::vector<uint8_t> generate();

private:
	// Statements from which to generate the machine code.
	std::vector<std::shared_ptr<Statement>> statements;

	// Instructions opcodes map.
	std::unordered_map<Statement::Instruction, uint8_t> opcodes = {
		{ Statement::Instruction::HALT,  0x00 }, { Statement::Instruction::ADD,   0x10 },
		{ Statement::Instruction::SUB,   0x11 }, { Statement::Instruction::AND,   0x12 },
		{ Statement::Instruction::OR,    0x13 }, { Statement::Instruction::XOR,   0x14 },
		{ Statement::Instruction::DROP,  0x20 }, { Statement::Instruction::DUP,   0x21 },
		{ Statement::Instruction::OVER,  0x22 }, { Statement::Instruction::SWAP,  0x23 },
		{ Statement::Instruction::STORE, 0x30 }, { Statement::Instruction::FETCH, 0x31 },
		{ Statement::Instruction::LIT,   0x40 }, { Statement::Instruction::IF,    0x50 },
		{ Statement::Instruction::CALL,  0x60 }, { Statement::Instruction::EXIT,  0x61 },
	};
};
