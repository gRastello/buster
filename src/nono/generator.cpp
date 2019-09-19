#include "generator.hpp"

Generator::Generator(std::vector<std::shared_ptr<Statement>> _statements) {
	statements = _statements;
}

Generator::~Generator() { }
