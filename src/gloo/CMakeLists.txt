cmake_minimum_required(VERSION 3.10)
project(gloo)

# c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# output directories
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../build")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../build")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../build")

# policies
cmake_policy(SET CMP0072 NEW) # modern GLVND over legacy OpenGL (libGL.so)
cmake_policy(SET CMP0012 NEW) # possible if(ON) in old cmake files; assimp
cmake_policy(SET CMP0111 NEW) # import target location; assimp
set(OpenGL_GL_PREFERENCE GLVND)

# path
#set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/glfw3")
list(APPEND CMAKE_PREFIX_PATH "/usr/lib64/cmake/glfw3" "/usr/lib64/cmake/assimp-5.0")

# libraries
find_package(OpenGL REQUIRED)
find_package(GLEW   REQUIRED)
find_package(glfw3  REQUIRED)
find_package(glm    REQUIRED)
#find_package(SOIL   REQUIRED) # does not exist on fedora
#find_package(assimp REQUIRED) # is incorrect on fedora

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SOIL REQUIRED soil)
find_library(SOIL_LIB         NAMES SOIL   PATHS /usr/lib64 /usr/local/lib /opt/local/lib                                  REQUIRED)
find_path   (SOIL_INCLUDE_DIR NAMES SOIL.h PATHS /usr/include /usr/include/SOIL /usr/local/include /opt/local/include/SOIL REQUIRED)

find_library(ASSIMP_LIB         NAMES assimp              PATHS /usr/lib64   REQUIRED)
find_path   (ASSIMP_INCLUDE_DIR NAMES assimp/Importer.hpp PATHS /usr/include REQUIRED)
# --> creating an imported target
add_library(assimp::assimp UNKNOWN IMPORTED)
set_target_properties(assimp::assimp PROPERTIES
  IMPORTED_LOCATION             "${ASSIMP_LIB}"
  INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
)

# source files
file(GLOB SRC_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h")
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin") # macos
  file(GLOB XTRA_SRC_FILES "../appcore/*.cpp" "../gl3rd/*.cpp")
  list(APPEND SRC_FILES ${XTRA_SRC_FILES})
endif()

# library definition/creation
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SOIL_INCLUDE_DIR} ../appcore ../gl3rd)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL GLEW::GLEW glfw ${SOIL_LIB} assimp::assimp)
