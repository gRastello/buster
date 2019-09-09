#include "lexer.hpp"

#include <iostream>

Lexer::Lexer(std::string &sourceCode) {
	source = sourceCode.begin();
	sourceEnd = sourceCode.end();
}

Lexer::~Lexer() { }

void Lexer::scan() {
	std::vector<Token> tokens;

	// Scan all tokens.
	while (source != sourceEnd) {
		lexemeStart = source;
		scanToken();
	}

	// Add the END token.
	lexemeStart = source;
	addToken(Token::Type::END);
}

void Lexer::addToken(Token::Type type) {
	std::string lexeme(lexemeStart, source);
	Token token(type, lexeme, line);
	tokens.push_back(token);
}

void Lexer::scanToken() {

	char c = *source;
	source++;

	if (c == '\n') {
		line++;
		return;
	}

	if (Lexer::isWhitespace(c)) return;

}

bool Lexer::isWhitespace(char c) {
	return c == ' ' || c == '\r' || c == '\t';
}
