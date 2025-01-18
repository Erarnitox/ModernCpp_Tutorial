#include <print>
#include <iostream>
#include <string>

int main() {
    std::print("Enter your Name:");
    std::string name;
    std::cin >> name;
    std::println("Hello {}!", name);
    return 0;
}