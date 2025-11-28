cmake_minimum_required(VERSION 3.28)
project(Raylib30Days LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Path to Raylib (MSVC precompiled)
set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib")

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add daily projects
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
