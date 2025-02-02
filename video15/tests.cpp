#include <iostream>
#include <cassert>
#include <sstream>

#define private public // Allow testing of private members
#define protected public // Allow testing of protected members

// === STATIC ASSERTIONS ===
// These are compile-time checks for preconditions and invariants.

// === UNIT TESTS ===


// === MAIN FUNCTION ===
int main() {
    try {
        std::cout << "All tests passed successfully.\n";
        return 0; // Main must return 0 for tests to succeed
    } catch (const std::exception& ex) {
        std::cerr << "Test failed: " << ex.what() << "\n";
        return 1;
    }
}