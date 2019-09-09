#include "token.hpp"

Token::Token(Type _type, std::string &_lexeme, uint64_t _line) {
	type   = _type;
	lexeme = _lexeme;
	line   = _line;
}

Token::~Token() { }

/* *********
 * OPERATORS
 * ********* */

bool operator==(const Token &lhs, const Token &rhs) {
	return (lhs.type == rhs.type) &&
	       (lhs.lexeme == rhs.lexeme) &&
		   (lhs.line == rhs.line);
}

bool operator!=(const Token &lhs, const Token &rhs) {
	return !(lhs == rhs);
}
