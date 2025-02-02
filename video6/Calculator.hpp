#pragma once

#include <functional>
#include <map>
#include <string>
#include <stdexcept>
#include <memory>

// Abstract base class (SOLID: Open/Closed Principle)
class IOperation {
public:
    virtual ~IOperation() = default;

    // Perform the operation
    virtual double execute(double a, double b) const = 0;
};

// Specific operation: Addition (SOLID: Single Responsibility Principle)
class Addition : public IOperation {
public:
    double execute(double a, double b) const override;
};

// Specific operation: Subtraction
class Subtraction : public IOperation {
public:
    double execute(double a, double b) const override;
};

// Calculator: Encapsulation & Dependency Injection (SOLID)
class Calculator {
public:
    Calculator() = default;

    // Register a new operation with a name
    void registerOperation(const std::string& name, const std::shared_ptr<IOperation>& operation);

    // Perform a calculation by name
    double calculate(const std::string& operationName, double a, double b) const;

    // Prevent copying
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;

private:
    std::map<std::string, std::shared_ptr<IOperation>> operations_;
};