#include <iostream>
#include <functional>
#include <vector>

// Example free function
int add(int a, int b) {
    return a + b;
}

// Example class with member function
class Multiplier {
public:
    explicit Multiplier(int factor) : factor_(factor) {}

    int multiply(int value) const {
        return value * factor_;
    }

private:
    int factor_;
};

// Function that takes std::function as a callback
void processNumbers(const std::vector<int>& numbers, std::function<void(int)> callback) {
    for (int num : numbers) {
        callback(num);
    }
}

int main() {
    // 1. Using std::function with a free function
    std::function<int(int, int)> func = add;
    std::cout << "Sum: " << func(3, 4) << '\n';

    // 2. Using std::function with a lambda
    std::function<int(int, int)> lambda = [](int x, int y) { return x * y; };
    std::cout << "Lambda product: " << lambda(3, 4) << '\n';

    // 3. Using std::function with a member function (via std::bind)
    Multiplier multiplier(5);
    std::function<int(int)> boundMultiply = std::bind(&Multiplier::multiply, multiplier, std::placeholders::_1);
    std::cout << "Bound multiply: " << boundMultiply(3) << '\n';

    // 4. Using std::function for callbacks
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    processNumbers(numbers, [](int num) { std::cout << "Processing: " << num << '\n'; });

    return 0;
}