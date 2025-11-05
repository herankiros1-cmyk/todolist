cmake_minimum_required(VERSION 3.10)
project(todolist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(todo_lib src/todo.cpp)

add_executable(todolist src/main.cpp)
target_link_libraries(todolist PRIVATE todo_lib)

enable_testing()

add_executable(test_todo test/test_todo.cpp)
target_link_libraries(test_todo PRIVATE todo_lib)
add_test(NAME todo_test COMMAND test_todo)
