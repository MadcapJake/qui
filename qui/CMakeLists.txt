# CMakeList.txt : CMake project for qui, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (qui "qui.cpp")

target_link_libraries(qui "scanner" "parser")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET qui PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
