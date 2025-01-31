cmake_minimum_required(VERSION 3.10)
project(ZPGproject)

# Nastavení standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# projects/libraries
add_subdirectory(appcore)
add_subdirectory(gloo)
add_subdirectory(gl3rd)
add_subdirectory(resources/reslib)
add_subdirectory(launcher)
