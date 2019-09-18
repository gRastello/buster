#include "analyzer.hpp"

Analyzer::Analyzer(std::vector<std::shared_ptr<Statement>> _statements) {
	statements = _statements;
}

Analyzer::~Analyzer() { }
