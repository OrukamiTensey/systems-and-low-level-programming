cmake_minimum_required(VERSION 3.16)
project(SystemsAndLowLevelEngineering C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# Options
add_compile_options(-Wall -Wextra -pedantic)

# Subdirectories / Modules
message(STATUS "Configuring Systems & Low-Level Suite...")

# Algorithms
add_executable(data_structures_heap
    cpp-algorithms/BinaryHeap.cpp
    cpp-algorithms/PriorityQueue.cpp
    cpp-algorithms/DynamicArray.cpp
)

# OS Synchronization Primitives
if(WIN32)
    add_executable(producers_consumers os-and-system-programming/Producers_consumers.cpp)
    add_executable(sleeping_barber os-and-system-programming/Sleeping_barber.cpp)
endif()
