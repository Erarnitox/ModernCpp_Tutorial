#include <iostream>
#include <memory>
#include "Calculator.hpp"

int main() {
    Calculator calculator;

    // Register operations
    calculator.registerOperation("add", std::make_shared<Addition>());
    calculator.registerOperation("subtract", std::make_shared<Subtraction>());

    // Perform calculations
    try {
        double result1 = calculator.calculate("add", 10.5, 5.2);
        std::cout << "10.5 + 5.2 = " << result1 << '\n';

        double result2 = calculator.calculate("subtract", 10.5, 5.2);
        std::cout << "10.5 - 5.2 = " << result2 << '\n';

        // Try an unknown operation
        double result3 = calculator.calculate("multiply", 10.5, 5.2);
        std::cout << "Result: " << result3 << '\n'; // Won't reach here
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
    }

    return 0;
}