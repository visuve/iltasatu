if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	file(GLOB iltasatu_lib_src "*.c" "*.cpp" "*.h" "*.hpp" "windows/*.cpp")
	add_library("iltasatu" SHARED ${iltasatu_lib_src})
else()
	file(GLOB iltasatu_lib_src "*.c" "*.cpp" "*.h" "*.hpp" "posix/*.cpp")
	add_library("iltasatu" SHARED ${iltasatu_lib_src})
endif()