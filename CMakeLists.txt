project("CMake-test")

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories($(CMAKE_CURRENT_SOURCE_DIR)/source)

add_executable(cmake_test source/main.cpp)
