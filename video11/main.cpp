#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // for std::accumulate

int main() {
    // Example dataset
    std::vector<int> vec = {10, 15, 20, 25, 30, 35};

    // 1. Drop the first 2 elements and iterate lazily over the remaining ones
    std::cout << "Elements starting from the 3rd: ";
    for (const auto& val : vec | std::ranges::views::drop(2)) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 2. Filter and transform: Get squares of even numbers
    std::cout << "Squares of even numbers: ";
    for (const auto& val : vec | std::ranges::views::filter([](int n) { return n % 2 == 0; }) 
                              | std::ranges::views::transform([](int n) { return n * n; })) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 3. Use std::ranges::count to count numbers greater than 20
    auto count_gt_20 = std::ranges::count_if(vec, [](int n) { return n > 20; });
    std::cout << "Count of elements > 20: " << count_gt_20 << "\n";

    // 4. Use std::ranges::find to locate the first occurrence of a value
    auto it = std::ranges::find(vec, 25);
    if (it != vec.end()) {
        std::cout << "Found 25 at index: " << std::distance(vec.begin(), it) << "\n";
    } else {
        std::cout << "25 not found\n";
    }

    // 5. Use std::ranges::find_if to locate the first odd number
    auto odd_it = std::ranges::find_if(vec, [](int n) { return n % 2 != 0; });
    if (odd_it != vec.end()) {
        std::cout << "First odd number: " << *odd_it << "\n";
    }

    // 6. Use std::ranges::all_of to check if all numbers are > 5
    bool all_gt_5 = std::ranges::all_of(vec, [](int n) { return n > 5; });
    std::cout << "All elements > 5: " << (all_gt_5 ? "Yes" : "No") << "\n";

    // 7. Use std::ranges::any_of to check if any number is divisible by 7
    bool any_divisible_by_7 = std::ranges::any_of(vec, [](int n) { return n % 7 == 0; });
    std::cout << "Any element divisible by 7: " << (any_divisible_by_7 ? "Yes" : "No") << "\n";

    // 8. Sort the range in descending order using std::ranges::sort
    std::ranges::sort(vec, std::ranges::greater{}); // Use custom comparator
    std::cout << "Sorted in descending order: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 9. Lazy concatenation of ranges using views::concat
    std::vector<int> extra = {40, 50};
    auto concatenated = std::ranges::views::concat(vec, extra);
    std::cout << "Concatenated range: ";
    for (const auto& val : concatenated) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 10. Using accumulate with ranges
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum of all elements: " << sum << "\n";

    return 0;
}