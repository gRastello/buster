#pragma once

#include "token.hpp"

#include <string>

class Statement {
public:
	Statement(std::string label, Token token);
	virtual ~Statement() = default;

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

#ifdef TEST
public:
	virtual std::string toString() = 0;

	std::string baseStr() {
		std::string str = "label: ";
		str += label;
		str += ", instruction: ";

		switch(instruction) {
		case Instruction::HALT:
			str += "HALT";
			break;
		case Instruction::ADD:
			str += "ADD";
			break;
		case Instruction::SUB:
			str += "SUB";
			break;
		case Instruction::OR:
			str += "OR";
			break;
		case Instruction::XOR:
			str += "XOR";
			break;
		case Instruction::DROP:
			str += "DROP";
			break;
		case Instruction::DUP:
			str += "DUP";
			break;
		case Instruction::OVER:
			str += "OVER";
			break;
		case Instruction::SWAP:
			str += "SWAP";
			break;
		case Instruction::STORE:
			str += "STORE";
			break;
		case Instruction::FETCH:
			str += "FETCH";
			break;
		case Instruction::LIT:
			str += "LIT";
			break;
		case Instruction::IF:
			str += "IF";
			break;
		case Instruction::CALL:
			str += "CALL";
			break;
		case Instruction::EXIT:
			str += "EXIT";
			break;
		default:
			str += "";
			break;
		}

		return str;
	}
#endif
};

class NoOperandStmt : public Statement {
public:
	NoOperandStmt(std::string label, Token token);
	~NoOperandStmt();

#ifdef TEST
public:
	std::string toString() {
		std::string str = "{ ";
		str += baseStr();
		str += " }";

		return str;
	}
#endif
};

class ImmediateStmt : public Statement {
public:
	ImmediateStmt(std::string label, Token token);
	~ImmediateStmt();

	uint8_t operand;

#ifdef TEST
public:
	std::string toString() {
		std::string str = "{ ";
		str += baseStr();
		str += ", operand:";
		str += operand;
		str += " }";

		return str;
	}
#endif
};

class LabelStmt : public Statement {
public:
	LabelStmt(std::string label, Token token);
	~LabelStmt();

	std::string operand;

#ifdef TEST
public:
	std::string toString() {
		std::string str = "{ ";
		str += baseStr();
		str += ", operand:";
		str += operand;
		str += " }";

		return str;
	}
#endif
};
