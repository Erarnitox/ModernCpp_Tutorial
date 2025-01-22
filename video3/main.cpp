#include <iostream>
#include <string>
#include <print>

import file_module;

int main() {
    std::print("Enter a Path:");
    std::string directory;
    std::cin >> directory;
    file_module::bulk_rename(directory);
    
    return 0;
}