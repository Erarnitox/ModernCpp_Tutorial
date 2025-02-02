#include "Calculator.hpp"

// Implementation of Addition
double Addition::execute(double a, double b) const {
    return a + b;
}

// Implementation of Subtraction
double Subtraction::execute(double a, double b) const {
    return a - b;
}

// Register a new operation
void Calculator::registerOperation(const std::string& name, const std::shared_ptr<IOperation>& operation) {
    if (operations_.find(name) != operations_.end()) {
        throw std::invalid_argument("Operation already exists: " + name);
    }
    operations_[name] = operation;
}

// Perform a calculation
double Calculator::calculate(const std::string& operationName, double a, double b) const {
    auto it = operations_.find(operationName);
    if (it == operations_.end()) {
        throw std::invalid_argument("Unknown operation: " + operationName);
    }
    return it->second->execute(a, b);
}