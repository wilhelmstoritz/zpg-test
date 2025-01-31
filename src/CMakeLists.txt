cmake_minimum_required(VERSION 3.10)
project(ZPGproject)

# project libraries
add_subdirectory(appcore)
add_subdirectory(gloo)
add_subdirectory(gl3rd)
add_subdirectory(resources/reslib)

# project executable
add_subdirectory(launcher)
