#pragma once

// standard C++ libraries
#include <vector>

// --- models ------------------------------------------------------------------
// triangle
extern std::vector<float> TRIANGLE_POINTS;
extern std::vector<float> TRIANGLE_POINTS_COLORDATA;

// square
extern std::vector<float> SQUARE_POINTS;

// --- shaders -----------------------------------------------------------------
// vertex shaders
extern const char* DEFAULT_VERTEX_SHADER;
extern const char* DEFAULT_VERTEX_SHADER_COLORFROMPOSITION;
extern const char* DEFAULT_VERTEX_SHADER_COLORDATA;

// fragment shaders
extern const char* DEFAULT_FRAGMENT_SHADER;
extern const char* DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION;
extern const char* DEFAULT_FRAGMENT_SHADER_COLORDATA;

extern const char* YELLOW_FRAGMENT_SHADER;
