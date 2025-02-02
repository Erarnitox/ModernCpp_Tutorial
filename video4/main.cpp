#include <iostream>    // For input/output
#include <vector>      // For dynamic arrays
#include <string>      // For string manipulation
#include <algorithm>   // For algorithms (e.g., sort, find)
#include <memory>      // For smart pointers
#include <optional>    // For optional values
#include <functional>  // For std::function
#include <thread>      // For multithreading
#include <future>      // For async tasks
#include <map>         // For associative containers
#include <ranges>      // C++20 ranges library
#include <map>
#include <set>
#include <tuple>
#include <fstream>
#include <stdexcept>

 // 24. Namespaces
namespace MyNamespace {
    void printMessage() {
        std::cout << "Message from MyNamespace!" << std::endl;
    }
}

// Base class for inheritance example
class Animal {
public:
    virtual void speak() const {
        std::cout << "Animal makes a sound\n";
    }
    virtual ~Animal() = default; // Virtual destructor for polymorphism
};

// Derived class
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog barks: Woof!\n";
    }
};

// Function demonstrating templates
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Function demonstrating lambdas and std::ranges
void processNumbers(const std::vector<int>& numbers) {
    auto isEven = [](int n) { return n % 2 == 0; };

    std::cout << "Even numbers: ";
    for (int n : numbers | std::ranges::views::filter(isEven)) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// Demonstrating RAII with std::unique_ptr
void demonstrateRAII() {
    std::unique_ptr<Animal> employee = std::make_unique<Dog>();
    employee->speak();
}

// Demonstrating std::async for concurrency
void demonstrateAsync() {
    auto asyncTask = std::async(std::launch::async, []() {
        std::cout << "Async task running...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 42;
    });

    std::cout << "Doing other work while waiting...\n";
    std::cout << "Result from async task: " << asyncTask.get() << "\n";
}

// Main function: Entry point of the program
int main() {
    // 1. Basic I/O
    std::cout << "Hello, World!" << std::endl;

    // 2. Variables and Data Types
    int integerVar = 42;
    double doubleVar = 3.14;
    char charVar = 'A';
    std::string stringVar = "C++ is powerful!";
    bool boolVar = true;

    // 3. Constants
    const int constantVar = 100;

    // 4. Control Structures
    if (integerVar > 0) {
        std::cout << "integerVar is positive." << std::endl;
    } else if (integerVar < 0) {
        std::cout << "integerVar is negative." << std::endl;
    } else {
        std::cout << "integerVar is zero." << std::endl;
    }

    // 5. Loops
    for (int i = 0; i < 5; ++i) {
        std::cout << "Loop iteration: " << i << std::endl;
    }

    int whileCounter = 0;
    while (whileCounter < 3) {
        std::cout << "While loop iteration: " << whileCounter << std::endl;
        whileCounter++;
    }

    // 6. Functions
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    std::cout << "5 + 7 = " << add(5, 7) << std::endl;

    // 8. Optionals for safe return values
    std::optional<std::string> maybeName = "Charlie";
    if (maybeName) {
        std::cout << "Optional name: " << *maybeName << "\n";
    }

    // 7. Arrays and Vectors (Dynamic Arrays)
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    numbers.push_back(6); // Add an element to the end

    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 8. Pointers and Smart Pointers
    int* ptr = &integerVar;
    std::cout << "Value of integerVar via pointer: " << *ptr << std::endl;

    std::unique_ptr<int> smartPtr = std::make_unique<int>(10);
    std::cout << "Value via smart pointer: " << *smartPtr << std::endl;

    // 9. Classes and Objects
    class MyClass {
    public:
        MyClass(const std::string& name) : name(name) {}
        void greet() const {
            std::cout << "Hello, " << name << "!" << std::endl;
        }
    private:
        std::string name;
    };

    MyClass myObject("Alice");
    myObject.greet();

    // 10. Inheritance
    class DerivedClass : public MyClass {
    public:
        DerivedClass(const std::string& name) : MyClass(name) {}
        void additionalGreet() {
            std::cout << "This is an additional greeting!" << std::endl;
        }
    };

    DerivedClass derivedObject("Bob");
    derivedObject.greet();
    derivedObject.additionalGreet();

    // 11. Polymorphism
    class Base {
    public:
        virtual void print() const {
            std::cout << "Base class print." << std::endl;
        }
    };

    class Derived : public Base {
    public:
        void print() const override {
            std::cout << "Derived class print." << std::endl;
        }
    };

    Base* basePtr = new Derived();
    basePtr->print();
    delete basePtr;

    // 12. Standard Template Library (STL) Algorithms
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 13. Error Handling (Exceptions)
    try {
        if (integerVar == 42) {
            throw std::runtime_error("Something went wrong!");
        }
    } catch (const std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    // 14. Modern C++ Features (Auto, Range-based for loops, Lambda)
    auto multiply = [](int a, int b) { return a * b; };
    std::cout << "3 * 4 = " << multiply(3, 4) << std::endl;

    // 15. File I/O
    std::ofstream file("example.txt");
    file << "Writing to a file." << std::endl;
    file.close();

    std::ifstream inputFile("example.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << "Read from file: " << line << std::endl;
    }

    // 16. Maps (Associative Containers)
    std::map<std::string, int> ageMap = {{"Alice", 25}, {"Bob", 30}};
    std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

    // 17. Sets
    std::set<int> uniqueNumbers = {1, 2, 2, 3, 4};
    for (int num : uniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 18. Tuples
    std::tuple<std::string, int, double> person = {"Charlie", 28, 5.9};
    std::cout << "Name: " << std::get<0>(person) << ", Age: " << std::get<1>(person) << std::endl;

    // 19. Function Objects (Functors)
    struct Square {
        int operator()(int x) const {
            return x * x;
        }
    };
    Square square;
    std::cout << "Square of 5: " << square(5) << std::endl;

    // 20. Function Pointers and std::function
    std::function<int(int, int)> func = add;
    std::cout << "Function pointer result: " << func(3, 4) << std::endl;

    // 21. Move Semantics
    std::vector<int> source = {1, 2, 3};
    std::vector<int> destination = std::move(source);
    std::cout << "Destination vector size: " << destination.size() << std::endl;

    // 22. Lambda Expressions with Captures
    int multiplier = 2;
    auto timesTwo = [multiplier](int x) { return x * multiplier; };
    std::cout << "2 * 5 = " << timesTwo(5) << std::endl;

    // 23. Type Inference (decltype)
    decltype(doubleVar) anotherDouble = 6.28;
    std::cout << "Another double: " << anotherDouble << std::endl;

    // 24. Namespaces
    MyNamespace::printMessage();

    // 25. Enumerations
    enum class Color { Red, Green, Blue };
    Color color = Color::Green;
    if (color == Color::Green) {
        std::cout << "The color is green!" << std::endl;
    }

    return 0;
}