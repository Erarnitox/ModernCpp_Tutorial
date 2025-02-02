#include "TodoList.hpp"


// Main function
int main() {
    ToDoList todo;

    todo.addTask(std::make_unique<SimpleTask>("Buy groceries"));
    todo.addTask(std::make_unique<ImportantTask>("Submit report"));
    todo.addTask(std::make_unique<SimpleTask>("Call John"));

    todo.displayTasks();

    std::cout << "\nRemoving front task...\n";
    todo.removeFront();
    todo.displayTasks();

    return 0;
}