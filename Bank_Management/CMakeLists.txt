# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Name your project
project(Bank-Application)



# Set the minimum required C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Specify that C++20 is required (optional, but recommended)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable and its source files
add_executable(my_binary src/main.cpp src/customer.cc src/staff.cc src/admin.cc )

# Specify include directories
target_include_directories(my_binary PUBLIC include)

target_link_libraries(my_binary sqlite3 crypto)




