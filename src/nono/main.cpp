#include "analyzer.hpp"
#include "generator.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argn, char **argv) {
	// Store relevant arguments in a vector.
	std::vector<std::string> arguments;
	uint64_t i;
	for (i = 1; i < argn; i++) arguments.push_back(argv[i]);

	// Check number of arguments.
	if (argn != 2) {
		std::cerr << "usage: nono [file]" << std::endl;
		std::exit(1);
	}

	// Get source code from the argument file.
	std::ifstream file;
	file.exceptions(std::ifstream::failbit);

	try {
		file.open(arguments[0], std::ios::binary);
	} catch (const std::exception &e) {
		std::cerr << "'" << arguments[0]
		          << "' does not exists or is not accessible" << std::endl;
		std::exit(1);
	}

	std::string sourceCode((std::istreambuf_iterator<char>(file)),
	                       (std::istreambuf_iterator<char>()));

	// Produce all the code.
	std::vector<uint8_t> code;

	try {
		// Lexing.
		Lexer lexer(sourceCode);
		lexer.scan(); 
	
		// Parsing.
		Parser parser(lexer.tokens);
		parser.parse();

		// Analyzation.
		Analyzer analyzer(parser.statements);
		analyzer.analyze();

		// Machine code generatiorn.
		Generator generator(parser.statements);
		code = generator.generate();
	} catch (LexingError &error) {
		std::cerr << "line " << error.line 
		          << ": " << error.message << std::endl;
	} catch (ParsingError &error) {
		std::cerr << "error at token: " << error.token.toString()
		          << ": " << error.message << std::endl;
	} catch (std::vector<AnalyzingError> &errors) {
		for (auto &error: errors) {
			std::cerr << "error: " << error.message << std::endl;
		}
	}

	// Last checks.
	if (code.size() > 0xFFFF) {
		std::cerr << "The generated code is bigger than Buster's RAM" 
		          << std::endl;
		std::exit(1);
	}

	// Dump the code to stdout.
	for (auto &byte: code) std::cout << byte;
}
