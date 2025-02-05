#pragma once

/* early tasks implementation; global data/variables */

// standard c++ libraries
#include <vector>

/*** 1st task ***/
// vertex shaders
extern const char* VSHADER_BASIC;
extern const char* VSHADER_COLORFROMPOSITION;
extern const char* VSHADER_COLORDATA;

// fragment shaders
extern const char* FSHADER_BASIC;
extern const char* FSHADER_COLORFROMPOSITION;
extern const char* FSHADER_COLORDATA;

extern const char* FSHADER_YELLOW;

/*** 2nd task ***/
extern const char* VSHADER_VIEW_PROJECTION_MATRIX;
extern const char* FSHADER_VIEW_PROJECTION_MATRIX;

/*** 3rd task ***/
extern const char* VSHADER_NORMAL;
extern const char* FSHADER_LAMBERTIAN;
extern const char* FSHADER_PHONG;
