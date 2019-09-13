#pragma once

#include "statement.hpp"
#include "token.hpp"

#include <memory>
#include <vector>

class Parser {
public:
	Parser(std::vector<Token> &tokens);
	~Parser();

private:
	// Iterators over the token stream.
	std::vector<Token>::iterator tokenStream;
	std::vector<Token>::iterator tokenStreamEnd;
	
	// Currently parsed statements.
	std::vector<std::shared_ptr<Statement>> statements;
};
