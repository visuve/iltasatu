cmake_minimum_required(VERSION 3.16)

project("iltasatu")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH "..")
set(LIBRARY_OUTPUT_PATH "..")

add_subdirectory("cli")
add_subdirectory("lib")

set(wxUSE_STL ON)
set(wxBUILD_SHARED OFF)

if(MSVC)
	add_compile_definitions(__WXMSW__ 1)
	add_compile_definitions(_UNICODE 1)
endif()

add_subdirectory("wxWidgets")
add_subdirectory("gui")