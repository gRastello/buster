#define TEST

#include "lexer.cpp"
#include "token.cpp"
#include "statement.cpp"
#include "parser.cpp"

#include <memory>
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

// Test instructions and identifiers lexing.
bool testLexerInstructionsIdentifiers() {
	std::string source = "CALL identifier";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.tokens.size() != 3) {
		reportMismatch("Lexer instructions and identifiers", 
					   "3",
					   lexer.tokens.size());
		return false;
	}

	std::string lexeme = "CALL";
	Token t(Token::Type::INSTRUCTION, lexeme, 1);
	if (lexer.tokens[0] != t) {
		reportMismatch("Lexer instruction and identifiers",
					   t.toString(),
					   lexer.tokens[0].toString());
		return false;
	}

	lexeme = "identifier";
	t = Token(Token::Type::IDENTIFIER, lexeme, 1);
	if (lexer.tokens[1] != t) {
		reportMismatch("Lexer instruction and identifiers",
					   t.toString(),
					   lexer.tokens[1].toString());
		return false;
	}

	return true;
}
	
// Lexer mixed (real worldish) test.
bool testLexerMixed() {
	std::string source = "foobar: 0x123c; this is a comment\n\tADD :";
	Lexer lexer(source);

	try {
		lexer.scan();
	} catch (LexingError &error) {
		std::cout << "Scan failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (lexer.tokens.size() != 6) {
		reportMismatch("Lexer mixed", "5", lexer.tokens.size());
		return false;
	}

	std::string lexeme = "foobar";
	Token t(Token::Type::IDENTIFIER, lexeme, 1);
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

	lexeme = "ADD";
	t = Token(Token::Type::INSTRUCTION, lexeme, 2);
	if (lexer.tokens[3] != t) {
		reportMismatch("Lexer mixed",
		               t.toString(),
					   lexer.tokens[3].toString());
		return false;
	}

	lexeme = ":";
	t = Token(Token::Type::COLON, lexeme, 2);
	if (lexer.tokens[4] != t) {
		reportMismatch("Lexer mixed",
		               t.toString(),
					   lexer.tokens[4].toString());
		return false;
	}

	return true;
}

// Test nooperation statement parsing.
bool testParserNoOperator() {
	// Make a token vector to parse.
	std::vector<Token> tokens;
	std::vector<std::shared_ptr<Statement>> results;
	std::string lexeme;

	lexeme = "HALT";
	Token t(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));

	lexeme = "ADD";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	lexeme = "SUB";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	lexeme = "OR";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	lexeme = "XOR";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	lexeme = "DROP";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));

	lexeme = "foo";
	t = Token(Token::Type::IDENTIFIER, lexeme, 1);
	tokens.push_back(t);

	lexeme = ":";
	t = Token(Token::Type::COLON, lexeme, 1);
	tokens.push_back(t);
	
	lexeme = "DUP";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("foo", t));
	
	lexeme = "OVER";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));

	lexeme = "label";
	t = Token(Token::Type::IDENTIFIER, lexeme, 1);
	tokens.push_back(t);

	lexeme = ":";
	t = Token(Token::Type::COLON, lexeme, 1);
	tokens.push_back(t);
	
	lexeme = "SWAP";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("label", t));
	
	lexeme = "STORE";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	lexeme = "FETCH";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	lexeme = "EXIT";
	t = Token(Token::Type::INSTRUCTION, lexeme, 1);
	tokens.push_back(t);
	results.push_back(std::make_shared<NooperatorStmt>("", t));
	
	// Parse.
	Parser parser(tokens);
	try {
		parser.parse();
	} catch (LexingError &error) {
		std::cout << "Parsing failed! Exception encountered!" << std::endl;
		return false;
	}

	// Check results.
	if (parser.statements.size() != 12) {
		reportMismatch("Parser nooperator", "12", parser.statements.size());
		return false;
	}

	for(int i = 0; i < results.size(); i++) {
		// Specialize pointer for parsed statements.
		std::shared_ptr<NooperatorStmt> parsed_noop =
			std::dynamic_pointer_cast<NooperatorStmt>(parser.statements[i]);
		std::shared_ptr<ImmediateStmt> parsed_immop =
			std::dynamic_pointer_cast<ImmediateStmt>(parser.statements[i]);
		std::shared_ptr<LabelStmt> parsed_labelop =
			std::dynamic_pointer_cast<LabelStmt>(parser.statements[i]);

		// Specialize pointer for correct results.
		std::shared_ptr<NooperatorStmt> result_noop =
			std::dynamic_pointer_cast<NooperatorStmt>(results[i]);
		std::shared_ptr<ImmediateStmt> result_immop =
			std::dynamic_pointer_cast<ImmediateStmt>(results[i]);
		std::shared_ptr<LabelStmt> result_labelop =
			std::dynamic_pointer_cast<LabelStmt>(results[i]);

		// Confront the two statements.
		if (parsed_noop && result_noop) {
			if (*parsed_noop != *result_noop) {
				reportMismatch("Parser nooperator", 
							   (*parsed_noop).toString(),
							   (*result_noop).toString());
				return false;
			}

			continue;
		}

		std::cout << "Expected a no-operand statement, found " 
		          << (parser.statements[i]->toString())
				  << std::endl;
		return false;
	}

	return true;
}

int main() {
	bool allPass = true;
	std::vector<Test> lexerTests = {
		{ "Lexer whitespace",                   &testLexerWhitespace              },
		{ "Lexer colon",                        &testLexerColon                   },
		{ "Lexer numbers",                      &testLexerNumbers                 },
		{ "Lexer numbers exceptions",           &testLexerNumbersExceptions       },
		{ "Lexer comments",                     &testLexerComments                },      
		{ "Lexer instructions and identifiers", &testLexerInstructionsIdentifiers },
		{ "Lexer mixed",                        &testLexerMixed                   },
	};

	std::vector<Test> parserTests = {
		{ "Parser nooperator", &testParserNoOperator },
	};

	for (auto &test: lexerTests) allPass = runTest(test);
	for (auto &test: parserTests) allPass = runTest(test);

	if (allPass) return 0;
	return 1;
}
