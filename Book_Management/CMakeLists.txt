# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Name your project
project(MyProject)

# Set the minimum required C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Specify that C++20 is required (optional, but recommended)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable and its source files
add_executable(my_project src/main.cpp)

target_link_libraries(my_project sqlite3)

# Specify include directories
target_include_directories(my_project PUBLIC include)



# You can also link to any libraries your project depends on
# target_link_libraries(my_project PRIVATE some_library)
