#include "statement.hpp"

Statement::Statement(std::string _label, Token token) {
	label = _label;
	
	// WARNIG: Yanderedev-level code below (I'll change this sooner or later 
	// (i.e. never)).
	if (token.lexeme == "HALT") {
		instruction = Statement::Instruction::HALT;
		return;
	}

	if (token.lexeme == "ADD") {
		instruction = Statement::Instruction::ADD;
		return;
	}

	if (token.lexeme == "SUB") {
		instruction = Statement::Instruction::SUB;
		return;
	}

	if (token.lexeme == "AND") {
		instruction = Statement::Instruction::AND;
		return;
	}

	if (token.lexeme == "OR") {
		instruction = Statement::Instruction::OR;
		return;
	}

	if (token.lexeme == "XOR") {
		instruction = Statement::Instruction::XOR;
		return;
	}

	if (token.lexeme == "DROP") {
		instruction = Statement::Instruction::DROP;
		return;
	}

	if (token.lexeme == "DUP") {
		instruction = Statement::Instruction::DUP;
		return;
	}

	if (token.lexeme == "OVER") {
		instruction = Statement::Instruction::OVER;
		return;
	}

	if (token.lexeme == "SWAP") {
		instruction = Statement::Instruction::SWAP;
		return;
	}

	if (token.lexeme == "STORE") {
		instruction = Statement::Instruction::STORE;
		return;
	}

	if (token.lexeme == "FETCH") {
		instruction = Statement::Instruction::FETCH;
		return;
	}

	if (token.lexeme == "LIT") {
		instruction = Statement::Instruction::LIT;
		return;
	}


	if (token.lexeme == "IF") {
		instruction = Statement::Instruction::IF;
		return;
	}

	if (token.lexeme == "CALL") {
		instruction = Statement::Instruction::CALL;
		return;
	}

	if (token.lexeme == "EXIT") {
		instruction = Statement::Instruction::EXIT;
		return;
	}
}

NoOperandStmt::NoOperandStmt(std::string label, Token token) 
	: Statement(label, token) { }

NoOperandStmt::~NoOperandStmt() { }

#ifdef TEST
bool operator==(NoOperandStmt &lhs, NoOperandStmt &rhs) {
	return lhs.instruction == rhs.instruction &&
	       lhs.label == rhs.label;
}

bool operator!=(NoOperandStmt &lhs, NoOperandStmt &rhs) {
	return !(lhs == rhs);
}
#endif

ImmediateStmt::ImmediateStmt(
	std::string label,
	Token instructionToken,
	Token immediateToken) : Statement(label, instructionToken) {
	std::string number(
		immediateToken.lexeme.begin() + 2,
		immediateToken.lexeme.end()
	);
	operand = std::stoi(number, nullptr, 16);
}

ImmediateStmt::~ImmediateStmt() { }

#ifdef TEST
bool operator==(ImmediateStmt &lhs, ImmediateStmt &rhs) {
	return lhs.instruction == rhs.instruction &&
	       lhs.label == rhs.label &&
		   lhs.operand == rhs.operand;
}

bool operator!=(ImmediateStmt &lhs, ImmediateStmt &rhs) {
	return !(lhs == rhs);
}
#endif

LabelStmt::LabelStmt(
	std::string label,
	Token instructionToken,
	Token labelToken) : Statement(label, instructionToken) {
	operand = labelToken.lexeme;
}

LabelStmt::~LabelStmt() { }

#ifdef TEST
bool operator==(LabelStmt &lhs, LabelStmt &rhs) {
	return lhs.instruction == rhs.instruction &&
	       lhs.label == rhs.label &&
		   lhs.operand == rhs.operand;
}

bool operator!=(LabelStmt &lhs, LabelStmt &rhs) {
	return !(lhs == rhs);
}
#endif
