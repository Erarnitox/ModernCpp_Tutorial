#include <iostream>
#include <cassert>
#include <sstream>

#define private public // Allow testing of private members
#define protected public // Allow testing of protected members

#include "TodoList.hpp" // Include the header for ToDoList and related classes

// === STATIC ASSERTIONS ===
// These are compile-time checks for preconditions and invariants.
static_assert(sizeof(TaskNode) <= 24, "TaskNode size should remain compact."); // Ensures XOR-linked list optimization
static_assert(sizeof(std::unique_ptr<Task>) == sizeof(void*), "std::unique_ptr size assumption is invalid."); // Prevent unexpected growth

// === UNIT TESTS ===
void test_add_task() {
    ToDoList todo;

    todo.addTask(std::make_unique<SimpleTask>("Task 1"));
    todo.addTask(std::make_unique<ImportantTask>("Task 2"));

    assert(todo.head != nullptr && "Head should not be null after adding tasks.");
    assert(todo.head->task->description == "Task 2" && "Head should point to the most recently added task.");
    assert(todo.head->xorPtr != nullptr && "Head should point to the next task.");
    std::cout << "test_add_task passed\n";
}

void test_remove_front() {
    ToDoList todo;

    todo.addTask(std::make_unique<SimpleTask>("Task 1"));
    todo.addTask(std::make_unique<ImportantTask>("Task 2"));
    todo.addTask(std::make_unique<SimpleTask>("Task 3"));

    // Remove the head task
    todo.removeFront();
    assert(todo.head->task->description == "Task 2" && "After removing, head should point to the second task.");
    todo.removeFront();
    assert(todo.head->task->description == "Task 1" && "After second removal, head should point to the first task.");
    todo.removeFront();
    assert(todo.head == nullptr && "Head should be null after removing all tasks.");
    std::cout << "test_remove_front passed\n";
}

void test_display_tasks() {
    ToDoList todo;
    todo.addTask(std::make_unique<SimpleTask>("Task 1"));
    todo.addTask(std::make_unique<ImportantTask>("Task 2"));

    // Capture the output of displayTasks
    std::ostringstream output = std::basic_ostringstream<char>();
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    todo.displayTasks();
    std::cout.rdbuf(oldCout); // Restore original stream buffer

    const std::string expected = "To-Do List:\n[Important] Task 2 (!!!)\n[Simple] Task 1\n";
    assert(output.str() == expected && "Display output does not match expected output.");
    std::cout << "test_display_tasks passed\n";
}

// === END-TO-END INTEGRATION TESTS ===
void test_integration_add_and_remove() {
    ToDoList todo;

    todo.addTask(std::make_unique<SimpleTask>("Buy groceries"));
    todo.addTask(std::make_unique<ImportantTask>("Submit report"));
    todo.addTask(std::make_unique<SimpleTask>("Call John"));

    // Check display
    std::ostringstream output = std::basic_ostringstream<char>();
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    todo.displayTasks();
    std::cout.rdbuf(oldCout); // Restore original stream buffer

    const std::string expectedBefore = "To-Do List:\n[Simple] Call John\n[Important] Submit report (!!!)\n[Simple] Buy groceries\n";
    assert(output.str() == expectedBefore && "Initial display does not match expected.");

    // Remove tasks and check
    todo.removeFront();
    output.str(""); // Clear the output stream
    todo.displayTasks();
    const std::string expectedAfter = "To-Do List:\n[Important] Submit report (!!!)\n[Simple] Buy groceries\n";
    assert(output.str() == expectedAfter && "Display after removing tasks does not match expected.");

    std::cout << "test_integration_add_and_remove passed\n";
}

// === MAIN FUNCTION ===
int main() {
    try {
        test_add_task();
        test_remove_front();
        test_display_tasks();
        test_integration_add_and_remove();

        std::cout << "All tests passed successfully.\n";
        return 0; // Main must return 0 for tests to succeed
    } catch (const std::exception& ex) {
        std::cerr << "Test failed: " << ex.what() << "\n";
        return 1;
    }
}