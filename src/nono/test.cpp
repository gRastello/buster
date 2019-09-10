#define TEST

#include "lexer.cpp"
#include "token.cpp"

#include <string>
#include <vector>

struct Test {
	std::string name;
	bool (* test)();
};

bool runTest(Test test) {
	bool result = (*test.test)();

	if (result) std::cout << test.name << ": PASS" << std::endl;
	return result;
}

void reportMismatch(std::string testName, std::string expected, uint64_t found) {
	std::cout << testName << ": FAILED" << std::endl;
	std::cout << "  expected " << expected << " but found " 
	          << found << std::endl;
}

void reportMismatch(std::string testName,
                    std::string expected,
					std::string found) {
	std::cout << testName << ": FAILED" << std::endl;
	std::cout << "  expected " << expected << " but found " 
	          << found << std::endl;
}

// Whitespace skipping lexing test.
bool testLexerWhitespace() {
	std::string source = "\n   \t\t  \r\n  \r\r\t  \n   \t";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.getLine() != 4) {
		reportMismatch("Lexer whitespace", "4", lexer.getLine());
		return false;
	}

	if (lexer.tokens.size() != 1) {
		reportMismatch("Lexer whitespace", "1", lexer.tokens.size());
		return false;
	}

	std::string lexeme = "";
	Token t(Token::Type::END, lexeme, 4);
	if (lexer.tokens[0] != t) {
		reportMismatch("Lexer whitespace",
		               t.toString(),
					   lexer.tokens[0].toString());
		return false;
	}

	return true;
}

// Test colon tokenization.
bool testLexerColon() {
	std::string source = "::";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.tokens.size() != 3) {
		reportMismatch("Lexer colon", "3", lexer.tokens.size());
		return false;
	}

	std::string lexeme = ":";
	Token t(Token::Type::COLON, lexeme, 1);

	if (lexer.tokens[0] != t) {
		reportMismatch("Lexer colon",
		               t.toString(),
					   lexer.tokens[0].toString());
		return false;
	}

	if (lexer.tokens[1] != t) {
		reportMismatch("Lexer colon",
		               t.toString(),
					   lexer.tokens[1].toString());
		return false;
	}

	return true;
}

// Test numbers tokenization.
bool testLexerNumbers() {
	std::string source = "0xAA01 0xFEC9";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.tokens.size() != 3) {
		reportMismatch("Lexer numbers", "3", lexer.tokens.size());
		return false;
	}

	std::string lexeme1 = "0xAA01";
	Token t1(Token::Type::NUMBER, lexeme1, 1);
	if (lexer.tokens[0] != t1) {
		reportMismatch("Lexer numbers",
		               t1.toString(),
					   lexer.tokens[0].toString());
		return false;
	}

	std::string lexeme2 = "0xFEC9";
	Token t2(Token::Type::NUMBER, lexeme2, 1);
	if (lexer.tokens[1] != t2) {
		reportMismatch("Lexer numbers",
		               t2.toString(),
					   lexer.tokens[1].toString());
		return false;
	}

	return true;
}

// Test lexing numbers exception throwing.
bool testLexerNumbersExceptions() {
	std::string source = "0xq";
	Lexer lexer(source);

	try {
		lexer.scan();
		std::cout << "Lexer numbers exceprions: FAILED"   << std::endl
		          << "  expected an exception, got none." << std::endl;
		return false;
	} catch (LexingError &error) { /* don't check exception contents */ }

	source = "0";
	lexer = Lexer(source);
	try {
		lexer.scan();
		std::cout << "Lexer numbers exceprions: FAILED"   << std::endl
		          << "  expected an exception, got none." << std::endl;
		return false;
	} catch (LexingError &error) { /* don't check exception contents */ }

	source = "0c";
	lexer = Lexer(source);
	try {
		lexer.scan();
		std::cout << "Lexer numbers exceprions: FAILED"   << std::endl
		          << "  expected an exception, got none." << std::endl;
		return false;
	} catch (LexingError &error) { /* don't check exception contents */  }

	return true;
} 

// Test comment skipping.
bool testLexerComments() {
	std::string source = "; foo bar baz\n;bar bar";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.tokens.size() != 1) {
		reportMismatch("Lexer comments", "1", lexer.tokens.size());
		return false;
	}

	std::string lexeme = "";
	Token t(Token::Type::END, lexeme, 2);
	if (lexer.tokens[0] != t) {
		reportMismatch("Lexer comments",
		               t.toString(),
					   lexer.tokens[0].toString());
		return false;
	}

	return true;
}
	
// Lexer mixed (real worldish) test.
bool testLexerMixed() {
	std::string source = "0xFF01 : 0x123c; this is a comment\n\t :";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.tokens.size() != 5) {
		reportMismatch("Lexer mixed", "5", lexer.tokens.size());
		return false;
	}

	std::string lexeme = "0xFF01";
	Token t(Token::Type::NUMBER, lexeme, 1);
	if (lexer.tokens[0] != t) {
		reportMismatch("Lexer mixed",
		               t.toString(),
					   lexer.tokens[0].toString());
		return false;
	}

	lexeme = ":";
	t = Token(Token::Type::COLON, lexeme, 1);
	if (lexer.tokens[1] != t) {
		reportMismatch("Lexer mixed",
		               t.toString(),
					   lexer.tokens[1].toString());
		return false;
	}

	lexeme = "0x123c";
	t = Token(Token::Type::NUMBER, lexeme, 1);
	if (lexer.tokens[2] != t) {
		reportMismatch("Lexer mixed",
		               t.toString(),
					   lexer.tokens[2].toString());
		return false;
	}

	lexeme = ":";
	t = Token(Token::Type::COLON, lexeme, 2);
	if (lexer.tokens[3] != t) {
		reportMismatch("Lexer mixed",
		               t.toString(),
					   lexer.tokens[3].toString());
		return false;
	}

	return true;
}

int main() {
	bool allPass = true;
	std::vector<Test> lexerTests = {
		{ "Lexer whitespace",         &testLexerWhitespace        },
		{ "Lexer colon",              &testLexerColon             },
		{ "Lexer numbers",            &testLexerNumbers           },
		{ "Lexer numbers exceptions", &testLexerNumbersExceptions },
		{ "Lexer comments",           &testLexerComments          },
		{ "Lexer mixed",              &testLexerMixed             },
	};

	for (auto &test: lexerTests) allPass = runTest(test);

	if (allPass) return 0;
	return 1;
}
