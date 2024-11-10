#pragma once

// standard C++ libraries
#include <vector>

// --- models ------------------------------------------------------------------
/* 1st task */
// triangle
extern std::vector<float> TRIANGLE_POINTS;
extern std::vector<float> TRIANGLE_POINTS_COLORDATA;

// square
extern std::vector<float> SQUARE_POINTS;

/* 2nd task */
// skybox
extern std::vector<float> SKYBOX;

// --- shaders -----------------------------------------------------------------
/* 1st task */
// vertex shaders
extern const char* DEFAULT_VERTEX_SHADER;
extern const char* DEFAULT_VERTEX_SHADER_COLORFROMPOSITION;
extern const char* DEFAULT_VERTEX_SHADER_COLORDATA;

// fragment shaders
extern const char* DEFAULT_FRAGMENT_SHADER;
extern const char* DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION;
extern const char* DEFAULT_FRAGMENT_SHADER_COLORDATA;

extern const char* YELLOW_FRAGMENT_SHADER;

/* 2nd task */
extern const char* TRANSFORMING_VERTEX_SHADER_NORMALDATA;
extern const char* TRANSFORMING_FRAGMENT_SHADER_NORMALDATA;
