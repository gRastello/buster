#include "token.hpp"

/* *********
 * OPERATORS
 * ********* */

bool operator==(const Token &lhs, const Token &rhs) {
	return (lhs.type == rhs.type) ||
	       (lhs.lexeme == rhs.lexeme) ||
		   (lhs.line == rhs.line);
}

bool operator!=(const Token &lhs, const Token &rhs) {
	return !(lhs == rhs);
}
