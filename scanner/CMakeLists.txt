cmake_minimum_required (VERSION 3.8)

add_library(scanner STATIC "Scanner.ixx" "Token.ixx")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET scanner PROPERTY CXX_STANDARD 20)
endif()