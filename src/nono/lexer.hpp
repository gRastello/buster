#pragma once

#include "token.hpp"

#include <string>
#include <vector>

class Lexer {
public:
	Lexer(std::string &sourceCode);
	~Lexer();
	
	// Scanned tokens.
	std::vector<Token> tokens;

	// Scan all the tokens.
	void scan();

private:
	// Iterators over the source code.
	std::string::iterator source;
	std::string::iterator sourceEnd;
	std::string::iterator lexemeStart;

	// Current line.
	uint64_t line = 1;

	// Add a new token of the given type to the `tokens` vector.
	void addToken(Token::Type type);

	// Scan a single token.
	void scanToken();

#ifdef TEST
public:
	int64_t getLine() { return line; }
#endif
};
