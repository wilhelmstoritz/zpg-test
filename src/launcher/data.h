#pragma once

// standard C++ libraries
#include <vector>

// --- models ------------------------------------------------------------------
// triangle
extern std::vector<float> TRIANGLE_POINTS;
extern std::vector<float> TRIANGLE_POINTS_COLORDATA;

// square
extern std::vector<float> SQUARE_POINTS;

// plane
extern std::vector<float> PLANE_POINTS;

// --- shaders -----------------------------------------------------------------
// vertex shaders
// --- default
extern const char* DEFAULT_VERTEX_SHADER;
extern const char* DEFAULT_VERTEX_SHADER_COLORFROMPOSITION;
extern const char* DEFAULT_VERTEX_SHADER_COLORDATA;

// --- transforming
extern const char* TRANSFORMING_VERTEX_SHADER_COLORDATA;

// fragment shaders
// --- default
extern const char* DEFAULT_FRAGMENT_SHADER;
extern const char* DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION;
extern const char* DEFAULT_FRAGMENT_SHADER_COLORDATA;

extern const char* YELLOW_FRAGMENT_SHADER;

// --- transforming
extern const char* TRANSFORMING_FRAGMENT_SHADER_COLORDATA;
