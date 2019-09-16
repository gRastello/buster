#pragma once

#include <string>

class Token {
public:
	enum class Type;
	Token();
	Token(Type type, std::string &lexeme, uint64_t line);
	~Token();

	// Type of the token.
	enum class Type { INSTRUCTION, IDENTIFIER, NUMBER, COLON, END };
	Type type;

	// Underlying lexeme.
	std::string lexeme;

	// Line number (for error reporting).
	uint64_t line;

#ifdef TEST
	std::string toString() {
		std::string str = "{ type: ";

		switch (type) {
		case Type::INSTRUCTION:
			str += "INSTRUCTION";
			break;
		case Type::IDENTIFIER:
			str += "IDENTIFIER";
			break;
		case Type::NUMBER:
			str += "NUMBER";
			break;
		case Type::COLON:
			str += "COLON";
		case Type::END:
			str += "END";
			break;
		default:
			break;
		}

		str += ", lexeme: ";
		str += lexeme;
		str += ", line: ";
		str += std::to_string(line);
		str += " }";

		return str;
	}
#endif
};
