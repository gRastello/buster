#include "parser.hpp"

Parser::Parser(std::vector<Token> &tokens) {
	tokenStream    = tokens.begin();
	tokenStreamEnd = tokens.end();
}

Parser::~Parser() { }

void Parser::parse() {
	while (tokenStream != tokenStreamEnd) statement();
}

void Parser::statement() {
	// Check for the optional label.
	std::string label = "";
	if ((*tokenStream).type == Token::Type::IDENTIFIER &&
	    (*(tokenStream + 1)).type == Token::Type::COLON) {
		label = (*tokenStream).lexeme;
		tokenStream += 2;
	}

	if (Parser::isNoOperator(*tokenStream)) noOperator(label);
	// Add the missing cases here. Throw something if nothing words.
}

void Parser::noOperator(std::string label) {
	statements.push_back(std::make_shared<NoOperandStmt>(label, *tokenStream));
	tokenStream++;
}

bool Parser::isNoOperator(Token &token) {
	return token.type == Token::Type::INSTRUCTION &&
	       (token.lexeme == "HALT"  || token.lexeme == "ADD"   ||
	        token.lexeme == "SUB"   || token.lexeme == "OR"    ||
		    token.lexeme == "XOR"   || token.lexeme == "DROP"  ||
			token.lexeme == "DUP"   || token.lexeme == "OVER"  ||
			token.lexeme == "STORE" || token.lexeme == "FETCH" ||
			token.lexeme == "SWAP"  || token.lexeme == "EXIT");
}
