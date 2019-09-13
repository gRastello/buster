#pragma once

#include "token.hpp"

#include <string>

class Statement {
public:
	Statement(std::string label, Token token);
	~Statement();

private:
	// Instruction in the statement.
	enum class Instruction {
		HALT, ADD,  SUB,   AND,
		OR,   XOR,  DROP,  DUP,
		OVER, SWAP, STORE, FETCH,
		LIT,  IF,   CALL,  EXIT
	};
	Instruction instruction;

	// Optional label for the statement.
	std::string label = "";
};

class NooperatorStmt : public Statement {
public:
	NooperatorStmt(std::string label, Token token);
	~NooperatorStmt();
};

class ImmediateStmt : public Statement {
public:
	ImmediateStmt();
	~ImmediateStmt();

private:
	uint8_t operand;
};

class LabelStmt : public Statement {
public:
	LabelStmt();
	~LabelStmt();

private:
	std::string operand;
};
