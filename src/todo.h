#pragma once

#include <string>
#include <vector>

struct Todo {
    int id;
    bool done;
    std::string text;
};

// DB file path (modifiable by tests)
extern std::string DB_FILE;

std::vector<Todo> loadTodos();
void saveTodos(const std::vector<Todo>& list);
int nextId(const std::vector<Todo>& list);

// Higher-level API used by main and tests
int addTodo(const std::string& text); // returns id
std::vector<Todo> listTodos();
bool markDone(int id);
bool removeTodo(int id);
void clearTodos();

void print_help();
