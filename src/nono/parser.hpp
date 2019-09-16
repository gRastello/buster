#pragma once

#include "statement.hpp"
#include "token.hpp"

#include <memory>
#include <vector>

class Parser {
public:
	Parser(std::vector<Token> &tokens);
	~Parser();
	
	// Parsed statements.
	std::vector<std::shared_ptr<Statement>> statements;
	
	// Parse the token stream.
	void parse();

private:
	// Iterators over the token stream.
	std::vector<Token>::iterator tokenStream;
	std::vector<Token>::iterator tokenStreamEnd;

	// Statement-parsing functions (their names should match more or less the 
	// names of the relative production rules in the grammar).
	void statement();
	void noOperator(std::string label);

	// Helper functions.
	static bool isNoOperator(Token &token);
};

class ParsingError {
public:
	ParsingError(std::string _message, Token _token);
	~ParsingError();

	// The error message.
	std::string message;
	// The problematic token.
	Token token;
};
