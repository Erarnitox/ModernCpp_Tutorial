#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class FileHandler {
public:
    explicit FileHandler(const std::string& filename, std::ios::openmode mode = std::ios::in);
    ~FileHandler();

    // Delete copy semantics to enforce RAII
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    // Move semantics for ownership transfer
    FileHandler(FileHandler&& other) noexcept;
    FileHandler& operator=(FileHandler&& other) noexcept;

    std::ifstream& getStream();
    bool isOpen() const;

private:
    std::ifstream fileStream_;
};

// CSV Parser class
class CSVParser {
public:
    explicit CSVParser(const std::string& filename, char delimiter = ',');
    
    std::vector<std::vector<std::string>> parse();

private:
    std::string filename_;
    char delimiter_;
};