cmake_minimum_required(VERSION 3.16)

project("iltasatu" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH "..")
set(LIBRARY_OUTPUT_PATH "..")

add_subdirectory("cli")
add_subdirectory("lib")