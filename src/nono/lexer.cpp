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

	// Parse a token or discard whitespace/comments.
	
	if (c == '\n') {
		line++;
		return;
	}

	if (Lexer::isWhitespace(c)) return;

	if (c == ';') {
		finishComment();
		return;
	}

	if (c == ':') {
		addToken(Token::Type::COLON);
		return;
	}

	if (c == '0') {
		finishNumber();
		return;
	}
}

void Lexer::finishComment() {
	while ( *source != '\n' && (source != sourceEnd)) source++;
}

void Lexer::finishNumber() {
	if (source == sourceEnd) {
		LexingError error(line, "unexpected EOF");
		throw error;
	}

	char c = *source;
	source++;

	if (c == 'x') {
		std::string::iterator digitsStart = source;

		// Get all the remaining digits.
		while (source != sourceEnd) {
			c = *source;
			source++;

			if (!isHexDigit(c)) {
				source--;
				break;
			}
		}

		// Throw if we got no digits.
		if (source == digitsStart) {
			LexingError error(line, "expected digits after 'x'");
			throw error;
		}

		addToken(Token::Type::NUMBER);
	} else {
		LexingError error(line, "expected 'x' after '0'");
		throw error;
	}
}

bool Lexer::isWhitespace(char c) {
	return c == ' ' || c == '\r' || c == '\t';
}

bool Lexer::isHexDigit(char c) {
	return (c >= 48 && c <= 57) ||
	       (c >= 65 && c <= 70) ||
		   (c >= 97 && c <= 102);
}

LexingError::LexingError(uint64_t _line, std::string _message) {
	line    = _line;
	message = _message;
}

LexingError::~LexingError() { }
