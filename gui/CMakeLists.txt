file(GLOB ILTASATU_GUI_SRC "*.cpp" "*.hpp")

if (MSVC)
add_executable("iltasatu_gui" WIN32 ${ILTASATU_GUI_SRC})
else()
add_executable("iltasatu_gui" ${ILTASATU_GUI_SRC})
endif()

target_precompile_headers("iltasatu_gui" PRIVATE "pch.hpp")
target_link_libraries("iltasatu_gui" "iltasatu" wx::core wx::base)