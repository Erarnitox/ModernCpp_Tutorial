#include <iostream>
#include "CSVParser.hpp"

int main() {
    try {
        CSVParser parser("data.csv");

        auto data = parser.parse();

        // Display parsed data
        for (const auto& row : data) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}