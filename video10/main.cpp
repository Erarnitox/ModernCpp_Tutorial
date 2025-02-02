#include <iostream>
#include <vector>
#include <algorithm>
#include <any>
#include <set>
#include <string>
#include <numeric> // for std::accumulate

// A helper to display any type stored in std::any
void displayAny(const std::any& data) {
    if (data.type() == typeid(int)) {
        std::cout << std::any_cast<int>(data);
    } else if (data.type() == typeid(double)) {
        std::cout << std::any_cast<double>(data);
    } else if (data.type() == typeid(std::string)) {
        std::cout << std::any_cast<std::string>(data);
    } else {
        std::cout << "Unknown type";
    }
}

// The heterogeneous data manager
class DataManager {
public:
    // Add an element of any type
    void add(const std::any& value) {
        data_.push_back(value);
    }

    // Display all stored elements
    void display() const {
        std::cout << "Data: ";
        for (const auto& element : data_) {
            displayAny(element);
            std::cout << " ";
        }
        std::cout << "\n";
    }

    // Remove elements of a specific type
    void removeByType(const std::type_info& type) {
        data_.erase(std::remove_if(data_.begin(), data_.end(), [&](const std::any& item) {
            return item.type() == type;
        }), data_.end());
    }

    // Find elements matching a predicate
    template <typename Predicate>
    std::vector<std::any> findIf(Predicate predicate) const {
        std::vector<std::any> results;
        std::copy_if(data_.begin(), data_.end(), std::back_inserter(results), predicate);
        return results;
    }

private:
    std::vector<std::any> data_; // Storage for heterogeneous data
};

// Helper function to print a vector of std::any
void displayAnyVector(const std::vector<std::any>& vec) {
    for (const auto& item : vec) {
        displayAny(item);
        std::cout << " ";
    }
    std::cout << "\n";
}

int main() {
    DataManager manager;

    // Add some heterogeneous data
    manager.add(42);
    manager.add(3.14);
    manager.add(std::string("Hello"));
    manager.add(99);
    manager.add(1.618);

    // Display all data
    manager.display();

    // Use std::find_if to find the first integer greater than 50
    auto results = manager.findIf([](const std::any& item) {
        return item.type() == typeid(int) && std::any_cast<int>(item) > 50;
    });

    std::cout << "Items greater than 50: ";
    displayAnyVector(results);

    // Remove all integers from the data
    manager.removeByType(typeid(int));
    std::cout << "After removing integers: ";
    manager.display();

    return 0;
}