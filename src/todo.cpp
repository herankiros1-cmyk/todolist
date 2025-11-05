#include "todo.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

std::string DB_FILE = "todos.db";

std::vector<Todo> loadTodos() {
    std::vector<Todo> list;
    std::ifstream in(DB_FILE);
    if (!in) return list;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        // format: id \t done(0/1) \t text
        std::istringstream ss(line);
        std::string part;
        std::getline(ss, part, '\t');
        int id = std::stoi(part);
        std::getline(ss, part, '\t');
        bool done = (part == "1");
        std::string text;
        std::getline(ss, text); // rest of line is text
        list.push_back({id, done, text});
    }
    return list;
}

void saveTodos(const std::vector<Todo>& list) {
    std::ofstream out(DB_FILE, std::ios::trunc);
    for (auto &t : list) {
        out << t.id << '\t' << (t.done ? "1" : "0") << '\t' << t.text << '\n';
    }
}

int nextId(const std::vector<Todo>& list) {
    int maxid = 0;
    for (auto &t : list) if (t.id > maxid) maxid = t.id;
    return maxid + 1;
}

int addTodo(const std::string& text) {
    auto todos = loadTodos();
    Todo t;
    t.id = nextId(todos);
    t.done = false;
    t.text = text;
    todos.push_back(t);
    saveTodos(todos);
    return t.id;
}

std::vector<Todo> listTodos() {
    return loadTodos();
}

bool markDone(int id) {
    auto todos = loadTodos();
    bool found = false;
    for (auto &t : todos) {
        if (t.id == id) {
            t.done = true;
            found = true;
            break;
        }
    }
    if (!found) return false;
    saveTodos(todos);
    return true;
}

bool removeTodo(int id) {
    auto todos = loadTodos();
    auto it = std::remove_if(todos.begin(), todos.end(), [&](const Todo& t){ return t.id == id; });
    if (it == todos.end()) {
        return false;
    }
    todos.erase(it, todos.end());
    saveTodos(todos);
    return true;
}

void clearTodos() {
    if (fs::exists(DB_FILE)) fs::remove(DB_FILE);
}

void print_help() {
    std::cout <<
        "TODO CLI\n"
        "Usage:\n"
        "  todolist add \"task description\"   Add a new task\n"
        "  todolist list                      List tasks\n"
        "  todolist done <id>                 Mark task done\n"
        "  todolist remove <id>               Remove task\n"
        "  todolist clear                     Remove all tasks\n"
        "  todolist help                      Show this message\n";
}
