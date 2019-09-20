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
}

void Lexer::addToken(Token::Type type) {
	std::string lexeme(lexemeStart, source);
	Token token(type, lexeme, line);
	tokens.push_back(token);
}

void Lexer::scanToken() {
	char c = *source;
	source++;

	// Discard newlines.
	if (c == '\n') {
		line++;
		return;
	}

	// Discard whitespace.
	if (Lexer::isWhitespace(c)) return;

	// Discard comments.
	if (c == ';') {
		finishComment();
		return;
	}

	// Tokenize ':'.
	if (c == ':') {
		addToken(Token::Type::COLON);
		return;
	}

	// Tokenize a number.
	if (c == '0') {
		finishNumber();
		return;
	}

	// Tokenize an instruction or identifier.
	if (isAlphanumeric(c)) {
		finishInstructionOrIdentifier();
		return;
	}

	// Throw exception for unexpected character.
	std::string message = "unexpected character '";
	message += c;
	message += '\'';
	LexingError error(line, message);
	throw error;
}

void Lexer::finishComment() {
	while (*source != '\n' && (source != sourceEnd)) source++;
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

void Lexer::finishInstructionOrIdentifier() {
	std::string::iterator lexemeStart = source - 1;
	while (isAlphanumeric(*source)) source++;

	std::string lexeme(lexemeStart, source);
	std::unordered_set<std::string>::iterator got = reservedWords.find(lexeme);
	if (got == reservedWords.end()) {
		addToken(Token::Type::IDENTIFIER);
	} else {
		addToken(Token::Type::INSTRUCTION);
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

bool Lexer::isAlphanumeric(char c) {
	return (c >= 48 && c <= 57) ||
		   (c >= 64 && c <= 90) ||
		   (c >= 97 && c <= 122);
}

LexingError::LexingError(uint64_t _line, std::string _message) {
	line    = _line;
	message = _message;
}

LexingError::~LexingError() { }
