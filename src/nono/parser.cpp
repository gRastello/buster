#include "parser.hpp"

Parser::Parser(std::vector<Token> &tokens) {
	tokenStream    = tokens.begin();
	tokenStreamEnd = tokens.end();
}

Parser::~Parser() { }
