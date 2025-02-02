#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cstdint> // for uintptr_t

// Base class representing a generic Task
class Task {
public:
    explicit Task(std::string desc) : description(std::move(desc)) {}
    virtual ~Task() = default;

    virtual void display() const {
        std::cout << "Task: " << description << "\n";
    }

protected:
    std::string description;
};

// Derived class representing a simple task
class SimpleTask : public Task {
public:
    explicit SimpleTask(const std::string& desc) : Task(desc) {}

    void display() const override {
        std::cout << "[Simple] " << description << "\n";
    }
};

// Derived class representing an important task
class ImportantTask : public Task {
public:
    explicit ImportantTask(const std::string& desc) : Task(desc) {}

    void display() const override {
        std::cout << "[Important] " << description << " (!!!)\n";
    }
};

// XOR Linked List Node
class TaskNode {
public:
    std::unique_ptr<Task> task;
    TaskNode* xorPtr = nullptr; // Stores (prev ^ next)

    explicit TaskNode(std::unique_ptr<Task> t) : task(std::move(t)) {}
};

// XOR Linked List for the To-Do List
class ToDoList {
public:
    ~ToDoList() {
        while (head) {
            removeFront();
        }
    }

    void addTask(std::unique_ptr<Task> task) {
        auto newNode = new TaskNode(std::move(task));
        newNode->xorPtr = head; // newNode->xorPtr = prev ^ next (nullptr ^ head)
        if (head) {
            head->xorPtr = xorPtrs(newNode, head->xorPtr);
        }
        head = newNode;
    }

    void removeFront() {
        if (!head) return;
        TaskNode* next = head->xorPtr; // Get next node
        if (next) {
            next->xorPtr = xorPtrs(head, next->xorPtr);
        }
        delete head;
        head = next;
    }

    void displayTasks() const {
        TaskNode* curr = head;
        TaskNode* prev = nullptr;
        TaskNode* next;

        std::cout << "To-Do List:\n";
        while (curr) {
            curr->task->display();
            next = xorPtrs(prev, curr->xorPtr);
            prev = curr;
            curr = next;
        }
    }

private:
    TaskNode* head = nullptr;

    static TaskNode* xorPtrs(TaskNode* a, TaskNode* b) {
        return reinterpret_cast<TaskNode*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
    }
};