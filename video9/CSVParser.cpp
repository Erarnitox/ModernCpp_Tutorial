#include "CSVParser.hpp"

// FileHandler Implementation
FileHandler::FileHandler(const std::string& filename, std::ios::openmode mode)
    : fileStream_(filename, mode) {
    if (!fileStream_.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

FileHandler::~FileHandler() {
    if (fileStream_.is_open()) {
        fileStream_.close();
    }
}

// Move Constructor
FileHandler::FileHandler(FileHandler&& other) noexcept
    : fileStream_(std::move(other.fileStream_)) {}

// Move Assignment Operator
FileHandler& FileHandler::operator=(FileHandler&& other) noexcept {
    if (this != &other) {
        fileStream_ = std::move(other.fileStream_);
    }
    return *this;
}

std::ifstream& FileHandler::getStream() {
    return fileStream_;
}

bool FileHandler::isOpen() const {
    return fileStream_.is_open();
}

// CSVParser Implementation
CSVParser::CSVParser(const std::string& filename, char delimiter)
    : filename_(filename), delimiter_(delimiter) {}

std::vector<std::vector<std::string>> CSVParser::parse() {
    FileHandler fileHandler(filename_);
    std::ifstream& file = fileHandler.getStream();

    std::vector<std::vector<std::string>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, delimiter_)) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}