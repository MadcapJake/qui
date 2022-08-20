cmake_minimum_required (VERSION 3.8)

add_library(parser STATIC   "Expression.ixx" "Parser.ixx")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET parser PROPERTY CXX_STANDARD 20)
endif()
