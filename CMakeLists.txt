# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("qui")

# Include sub-projects.
add_subdirectory("scanner")
add_subdirectory ("qui")




add_subdirectory("parser")
