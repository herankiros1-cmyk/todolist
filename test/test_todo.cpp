#include "../src/todo.h"

#include <cassert>
#include <cstdio>
#include <iostream>

int main() {
    // Use an isolated DB file for tests
    DB_FILE = "test_todos.db";
    // ensure clean state
    std::remove(DB_FILE.c_str());

    int id1 = addTodo("unit task 1");
    assert(id1 == 1);

    auto list = listTodos();
    assert(list.size() == 1);
    assert(list[0].text == "unit task 1");
    assert(!list[0].done);

    bool ok = markDone(id1);
    assert(ok);
    list = listTodos();
    assert(list.size() == 1 && list[0].done);

    bool removed = removeTodo(id1);
    assert(removed);
    list = listTodos();
    assert(list.empty());

    // cleanup
    std::remove(DB_FILE.c_str());

    std::cout << "All tests passed\n";
    return 0;
}
