cmake_minimum_required(VERSION 3.10)
project(reslib)

# c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# output directories
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../build")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../build")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../build")

# policies
cmake_policy(SET CMP0072 NEW) # modern GLVND over legacy OpenGL (libGL.so)
set(OpenGL_GL_PREFERENCE GLVND)

# path
set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/glfw3")

# libraries
find_package(OpenGL REQUIRED)
find_package(GLEW   REQUIRED)
find_package(glfw3  REQUIRED)
find_package(glm    REQUIRED)

# source files
file(GLOB SRC_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h")
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin") # macos
  file(GLOB XTRA_SRC_FILES "../../appcore/*.cpp")
  list(APPEND SRC_FILES ${XTRA_SRC_FILES})
endif()

# library definition/creation
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE ../../appcore)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL GLEW::GLEW glfw)
