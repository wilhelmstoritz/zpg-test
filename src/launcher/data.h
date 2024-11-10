#pragma once

// standard C++ libraries
#include <vector>

// --- models ------------------------------------------------------------------
/* 1st task */
// triangle
extern std::vector<float> MODEL_TRIANGLE;
extern std::vector<float> MODEL_TRIANGLE_COLORDATA;

// square
extern std::vector<float> MODEL_SQUARE;

/* 2nd task */
// skybox
extern std::vector<float> MODEL_SKYBOX;

// --- shaders -----------------------------------------------------------------
/* 1st task */
// vertex shaders
extern const char* BASIC_VSHADER;
extern const char* BASIC_VSHADER_COLORFROMPOSITION;
extern const char* BASIC_VSHADER_COLORDATA;

// fragment shaders
extern const char* BASIC_FSHADER;
extern const char* BASIC_FSHADER_COLORFROMPOSITION;
extern const char* BASIC_FSHADER_COLORDATA;

extern const char* BASIC_FSHADER_YELLOW;

/* 2nd task */
extern const char* VSHADER_VIEW_PROJECTION;
extern const char* FSHADER_VIEW_PROJECTION;

/* 3rd task */
extern const char* VSHADER_NORMAL;
extern const char* FSHADER_LAMBERTIAN;
extern const char* FSHADER_PHONG;

// --- tmp ---------------------------------------------------------------------
extern const char* VSHADER_TMP;
extern const char* FSHADER_TMP;
