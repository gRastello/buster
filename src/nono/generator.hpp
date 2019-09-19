#pragma once

#include "statement.hpp"

#include <memory>
#include <vector>

class Generator {
public:
	Generator(std::vector<std::shared_ptr<Statement>> _statements);
	~Generator();

private:
	// Statements from which to generate the machine code.
	std::vector<std::shared_ptr<Statement>> statements;
};
