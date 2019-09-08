#include <string>

class Token {
public:
	// Type of the token.
	enum class Type { INSTRUCTION, IDENTIFIER, NUMBER };
	Type type;

	// Underlying lexeme.
	std::string lexeme;

	// Line number (for error reporting).
	uint64_t line;
};
