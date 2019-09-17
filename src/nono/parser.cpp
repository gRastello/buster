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

	if (Parser::isNoOperand(*tokenStream)) {
		noOperand(label);
		return;
	}

	if (Parser::isImmediateOperand(*tokenStream)) {
		immediateOperand(label);
		return;
	}

	if (Parser::isLabelOperand(*tokenStream)) {
		labelOperand(label);
		return;
	}

	throw ParsingError("No matching production rule for token", *tokenStream);
}

void Parser::noOperand(std::string label) {
	statements.push_back(std::make_shared<NoOperandStmt>(label, *tokenStream));
	tokenStream++;
}

void Parser::immediateOperand(std::string label) {
	Token instructionToken = *tokenStream;
	tokenStream++;

	if (tokenStream != tokenStreamEnd) {
		if (tokenStream->type == Token::Type::NUMBER) {
			statements.push_back(std::make_shared<ImmediateStmt>(
				label,
				instructionToken,
				*tokenStream
			));
			tokenStream++;
			return;
		}

		throw ParsingError("expected number but found", *tokenStream);
	}

	throw ParsingError("premature end of stream after", *(tokenStream - 1));
}

void Parser::labelOperand(std::string label) {
	Token instructionToken = *tokenStream;
	tokenStream++;

	if (tokenStream != tokenStreamEnd) {
		if (tokenStream->type == Token::Type::IDENTIFIER) {
			statements.push_back(std::make_shared<LabelStmt>(
				label,
				instructionToken,
				*tokenStream
			));
			tokenStream++;
			return;
		}

		throw ParsingError("expected identifier but found", *tokenStream);
	}

	throw ParsingError("premature end of stream after", *(tokenStream - 1));
}

bool Parser::isNoOperand(Token &token) {
	return token.type == Token::Type::INSTRUCTION &&
	       (token.lexeme == "HALT"  || token.lexeme == "ADD"   ||
	        token.lexeme == "SUB"   || token.lexeme == "OR"    ||
		    token.lexeme == "XOR"   || token.lexeme == "DROP"  ||
			token.lexeme == "DUP"   || token.lexeme == "OVER"  ||
			token.lexeme == "STORE" || token.lexeme == "FETCH" ||
			token.lexeme == "SWAP"  || token.lexeme == "EXIT");
}

bool Parser::isImmediateOperand(Token &token) {
	return token.type == Token::Type::INSTRUCTION && token.lexeme == "LIT";
}

bool Parser::isLabelOperand(Token &token) {
	return token.type == Token::Type::INSTRUCTION &&
	       (token.lexeme == "IF" || token.lexeme == "CALL");
}

ParsingError::ParsingError(std::string _message, Token _token) {
	message = _message;
	token = _token;
}

ParsingError::~ParsingError() { }
