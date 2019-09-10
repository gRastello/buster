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
	void finishComment();
	void finishNumber();

	// Check if `c` is whitespace.
	static bool isWhitespace(char c);
	static bool isHexDigit(char c);

#ifdef TEST
public:
	int64_t getLine() { return line; }
#endif
};

class LexingError {
public:
	LexingError(uint64_t _line, std::string _message);
	~LexingError();

private:
	// Line of the problematic token.
	uint64_t line;
	// Error message.
	std::string message;
};
