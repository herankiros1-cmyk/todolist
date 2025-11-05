#include "todo.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        print_help();
        return 0;
    }
    std::string cmd = argv[1];
    if (cmd == "add") {
        if (argc < 3) {
            std::cout << "Please provide task text.\n";
            return 1;
        }
        std::string text;
        for (int i = 2; i < argc; ++i) {
            if (i > 2) text += " ";
            text += argv[i];
        }
        int id = addTodo(text);
        std::cout << "Added [" << id << "] " << text << '\n';
    } else if (cmd == "list") {
        auto todos = listTodos();
        if (todos.empty()) {
            std::cout << "No tasks.\n";
            return 0;
        }
        for (auto &t : todos) {
            std::cout << (t.done ? "[x] " : "[ ] ") << t.id << ": " << t.text << '\n';
        }
    } else if (cmd == "done") {
        if (argc != 3) { std::cout << "Usage: todolist done <id>\n"; return 1; }
        int id = std::stoi(argv[2]);
        if (markDone(id)) std::cout << "Marked done: " << id << '\n';
        else std::cout << "Task not found: " << id << '\n';
    } else if (cmd == "remove") {
        if (argc != 3) { std::cout << "Usage: todolist remove <id>\n"; return 1; }
        int id = std::stoi(argv[2]);
        if (removeTodo(id)) std::cout << "Removed: " << id << '\n';
        else std::cout << "Task not found: " << id << '\n';
    } else if (cmd == "clear") {
        clearTodos();
        std::cout << "All tasks cleared.\n";
    } else if (cmd == "help") {
        print_help();
    } else {
        std::cout << "Unknown command: " << cmd << '\n';
        print_help();
    }
    return 0;
}
