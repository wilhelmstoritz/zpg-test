cmake_minimum_required(VERSION 3.10)
project(ZPGproject)

# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# project libraries
add_subdirectory(appcore)
add_subdirectory(gloo)
add_subdirectory(gl3rd)
add_subdirectory(resources/reslib)

# project executable
add_subdirectory(launcher)
