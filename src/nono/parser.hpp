#pragma once

#include "statement.hpp"
#include "token.hpp"

#include <memory>
#include <vector>

class Parser {
public:
	Parser(std::vector<Token> &tokens);
	~Parser();
	
	// Parse the token stream.
	void parse();

private:
	// Iterators over the token stream.
	std::vector<Token>::iterator tokenStream;
	std::vector<Token>::iterator tokenStreamEnd;
	
	// Currently parsed statements.
	std::vector<std::shared_ptr<Statement>> statements;

	// Statement-parsing functions (their names should match more or less the 
	// names of the relative production rules in the grammar).
	void statement();
	void noOperator(std::string label);

	// Helper functions.
	static bool isNoOperator(Token &token);
};
