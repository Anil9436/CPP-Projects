# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Name your project
project(BookManagement_system)

# Set the minimum required C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Specify that C++20 is required (optional, but recommended)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable and its source files
add_executable(my_binary src/main.cpp src/suppliers.cpp src/books_details.cpp src/employee_details.cpp)

target_link_libraries(my_binary sqlite3)

# Specify include directories
target_include_directories(my_binary PUBLIC include)

