#pragma once

#include "statement.hpp"

#include <memory>
#include <vector>

class AnalyzingError {
public:
	AnalyzingError(std::string _message);
	~AnalyzingError();

private:
	// Error message.
	std::string message;
};

class Analyzer {
public:
	Analyzer(std::vector<std::shared_ptr<Statement>> _statements);
	~Analyzer();

	// Analyze the given tokens. Throw exceptions if something is wrong.
	void analyze();

private:
	// Statements to analyze.
	std::vector<std::shared_ptr<Statement>> statements;

	// Check that all labels are meaningful.
	std::vector<AnalyzingError> checkLabels();
};
