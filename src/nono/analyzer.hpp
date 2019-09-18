#pragma once

#include "statement.hpp"

#include <memory>
#include <vector>

class Analyzer {
public:
	Analyzer(std::vector<std::shared_ptr<Statement>> _statements);
	~Analyzer();

private:
	// Statements to analyze.
	std::vector<std::shared_ptr<Statement>> statements;
};
