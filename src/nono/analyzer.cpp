#include "analyzer.hpp"

#include <unordered_set>

AnalyzingError::AnalyzingError(std::string _message) {
	message = _message;
}

AnalyzingError::~AnalyzingError() { }

Analyzer::Analyzer(std::vector<std::shared_ptr<Statement>> _statements) {
	statements = _statements;
}

Analyzer::~Analyzer() { }

void Analyzer::analyze() {
	std::vector<AnalyzingError> errors;

	std::vector<AnalyzingError> v = checkLabels();
	errors.insert(errors.end(), v.begin(), v.end());

	if (errors.size() != 0) throw errors;
}

std::vector<AnalyzingError> Analyzer::checkLabels() {
	std::vector<AnalyzingError> errors;

	// Create a set of labels.
	std::unordered_set<std::string> labels;
	for (auto &stmt: statements) labels.insert(stmt->label);

	// Check if all label-type statements have meaningful labels.
	for (auto &stmt: statements) {
		std::shared_ptr<LabelStmt> labelStmt =
			std::dynamic_pointer_cast<LabelStmt>(stmt);

		if (labelStmt) {
			std::unordered_set<std::string>::const_iterator it = 
				labels.find(labelStmt->operand);

			if (it == labels.end()) {
				errors.push_back(
					AnalyzingError("nonexsisting label: " + labelStmt->operand)
				);
			}
		}
	}

	return errors;
}
